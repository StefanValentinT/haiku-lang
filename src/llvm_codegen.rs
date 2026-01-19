use std::collections::HashSet;

use crate::{
    ast::ast_type::Type,
    tac::{TacBinaryOp, TacConst, TacFuncDef, TacInstruction, TacProgram, TacUnaryOp, TacVal},
};

pub fn emit_llvm(program: &TacProgram) -> String {
    let TacProgram::Program(funcs) = program;

    let mut defined = HashSet::new();
    let mut externs = HashSet::new();

    for f in funcs {
        let TacFuncDef::Function { name, .. } = f;
        defined.insert(name.clone());
    }

    let mut reg_counter = 0;
    let mut out = String::new();

    for f in funcs {
        out.push_str(&emit_function(f, &defined, &mut externs, &mut reg_counter));
        out.push('\n');
    }

    let mut header = String::new();
    for e in externs {
        header.push_str(&format!("declare i32 @{}(...)\n", e));
    }

    if !header.is_empty() {
        header.push('\n');
    }

    header + &out
}

fn emit_function(
    func: &TacFuncDef,
    defined: &HashSet<String>,
    externs: &mut HashSet<String>,
    reg_counter: &mut usize,
) -> String {
    *reg_counter = 0;

    let TacFuncDef::Function {
        name,
        params,
        ret_type,
        body,
    } = func;

    if body.is_empty() {
        return format!(
            "declare {} @{}({})\n",
            llvm_type(ret_type),
            name,
            params
                .iter()
                .map(|_| "i32".to_string())
                .collect::<Vec<_>>()
                .join(", ")
        );
    }

    let locals = collect_locals(body, params);

    let mut out = String::new();

    let ret_llvm_ty = llvm_type(ret_type);

    out.push_str(&format!(
        "define {} @{}({}) {{\n",
        ret_llvm_ty,
        name,
        params
            .iter()
            .map(|p| format!("{} %arg_{}", "i32", p))
            .collect::<Vec<_>>()
            .join(", ")
    ));

    out.push_str("entry:\n");

    for (v, ty) in &locals {
        if !params.contains(v) {
            if *ty != Type::Unit {
                let llvm_ty = llvm_type(ty);
                out.push_str(&format!("  %{} = alloca {}\n", v, llvm_ty));
            }
        }
    }

    for p in params {
        out.push_str(&format!(
            "  %{} = alloca i32\n  store i32 %arg_{}, i32* %{}\n",
            p, p, p
        ));
    }

    let mut terminated = false;

    for instr in body {
        if let TacInstruction::Label(l) = instr {
            if !terminated {
                out.push_str(&format!("  br label %{}\n", l));
            }
            out.push_str(&format!("{}:\n", l));
            terminated = false;
            continue;
        }

        out.push_str(&emit_instr(instr, defined, externs, reg_counter));

        terminated = matches!(
            instr,
            TacInstruction::Return(_)
                | TacInstruction::Jump { .. }
                | TacInstruction::JumpIfZero { .. }
                | TacInstruction::JumpIfNotZero { .. }
        );
    }

    if !terminated {
        match ret_type {
            Type::Unit => {
                out.push_str("  ret void\n");
            }
            _ => {
                out.push_str("  unreachable\n");
            }
        }
    }

    out.push_str("}\n");
    out
}

fn emit_instr(
    instr: &TacInstruction,
    defined: &HashSet<String>,
    externs: &mut HashSet<String>,
    reg_counter: &mut usize,
) -> String {
    match instr {
        TacInstruction::Return(v_opt) => match v_opt {
            None => "  ret void\n".to_string(),
            Some(TacVal::Var(_, Type::Unit)) => "  ret void\n".to_string(),
            Some(val) => {
                let (load, val_str, ty) = load_val(val, reg_counter);
                format!("{}  ret {} {}\n", load, ty, val_str)
            }
        },
        TacInstruction::Copy { src, dest } => {
            let (load, val, ty) = load_val(src, reg_counter);
            format!(
                "{}  store {} {}, {}* %{}\n",
                load,
                ty,
                val,
                ty,
                var_name(dest)
            )
        }
        TacInstruction::Unary { op, src, dest } => {
            let (load, val, ty) = load_val(src, reg_counter);
            let r = fresh_reg(reg_counter);

            let op_ir = match op {
                TacUnaryOp::Negate => format!("sub {} 0, {}", ty, val),
                TacUnaryOp::Complement => format!("xor {} {}, -1", ty, val),
                TacUnaryOp::Not => {
                    let c = fresh_reg(reg_counter);
                    return format!(
                        "{}  {} = icmp eq {} {}, 0\n  {} = zext i1 {} to i32\n  store i32 {}, i32* %{}\n",
                        load,
                        c,
                        ty,
                        val,
                        r,
                        c,
                        r,
                        var_name(dest)
                    );
                }
            };

            format!(
                "{}  {} = {}\n  store {} {}, {}* %{}\n",
                load,
                r,
                op_ir,
                ty,
                r,
                ty,
                var_name(dest)
            )
        }
        TacInstruction::Binary {
            op,
            src1,
            src2,
            dest,
        } => {
            let (a_load, a, ty) = load_val(src1, reg_counter);
            let (b_load, b, _) = load_val(src2, reg_counter);
            let r = fresh_reg(reg_counter);

            if matches!(op, TacBinaryOp::Divide | TacBinaryOp::Remainder) {
                match src2 {
                    TacVal::Constant(TacConst::I32(0))
                    | TacVal::Constant(TacConst::I64(0))
                    | TacVal::Constant(TacConst::F64(0.0)) => {
                        panic!("Compile-time error: division or remainder by zero");
                    }
                    _ => {}
                }
            }

            let ir = match op {
                TacBinaryOp::Add => {
                    if ty == "double" {
                        format!("fadd double {}, {}", a, b)
                    } else {
                        format!("add {} {}, {}", ty, a, b)
                    }
                }
                TacBinaryOp::Subtract => {
                    if ty == "double" {
                        format!("fsub double {}, {}", a, b)
                    } else {
                        format!("sub {} {}, {}", ty, a, b)
                    }
                }
                TacBinaryOp::Multiply => {
                    if ty == "double" {
                        format!("fmul double {}, {}", a, b)
                    } else {
                        format!("mul {} {}, {}", ty, a, b)
                    }
                }
                TacBinaryOp::Divide => {
                    if ty == "double" {
                        format!("fdiv double {}, {}", a, b)
                    } else {
                        let trap_check = fresh_reg(reg_counter);
                        let cont_label = format!("div_cont{}", reg_counter);
                        let trap_ir = format!(
                            "  {} = icmp eq {} {}, 0\n  br i1 {}, label %div_zero, label %{}\ndiv_zero:\n  call void @llvm.trap()\n  unreachable\n{}:\n",
                            trap_check, ty, b, trap_check, cont_label, cont_label
                        );
                        let ir = format!("sdiv {} {}, {}", ty, a, b);
                        let full = format!("{}{}  {}\n{}", a_load, b_load, ir, trap_ir);
                        return full;
                    }
                }
                TacBinaryOp::Remainder => {
                    if ty == "double" {
                        panic!("Remainder not supported for floating-point types in LLVM");
                    } else {
                        format!("srem {} {}, {}", ty, a, b)
                    }
                }

                TacBinaryOp::Equal
                | TacBinaryOp::NotEqual
                | TacBinaryOp::LessThan
                | TacBinaryOp::LessOrEqual
                | TacBinaryOp::GreaterThan
                | TacBinaryOp::GreaterOrEqual => {
                    let r_icmp = fresh_reg(reg_counter);
                    let cmp_ir = if ty == "double" {
                        let pred = match op {
                            TacBinaryOp::Equal => "oeq",
                            TacBinaryOp::NotEqual => "one",
                            TacBinaryOp::LessThan => "olt",
                            TacBinaryOp::LessOrEqual => "ole",
                            TacBinaryOp::GreaterThan => "ogt",
                            TacBinaryOp::GreaterOrEqual => "oge",
                            _ => unreachable!(),
                        };
                        format!("{} = fcmp {} double {}, {}", r_icmp, pred, a, b)
                    } else {
                        let pred = match op {
                            TacBinaryOp::Equal => "eq",
                            TacBinaryOp::NotEqual => "ne",
                            TacBinaryOp::LessThan => "slt",
                            TacBinaryOp::LessOrEqual => "sle",
                            TacBinaryOp::GreaterThan => "sgt",
                            TacBinaryOp::GreaterOrEqual => "sge",
                            _ => unreachable!(),
                        };
                        format!("{} = icmp {} {} {}, {}", r_icmp, pred, ty, a, b)
                    };
                    let zext = fresh_reg(reg_counter);
                    return format!(
                        "{}{}  {}\n  {} = zext i1 {} to i32\n  store i32 {}, i32* %{}\n",
                        a_load,
                        b_load,
                        cmp_ir,
                        zext,
                        r_icmp,
                        zext,
                        var_name(dest)
                    );
                }

                _ => unreachable!(),
            };

            format!(
                "{}{}  {} = {}\n  store {} {}, {}* %{}\n",
                a_load,
                b_load,
                r,
                ir,
                ty,
                r,
                ty,
                var_name(dest)
            )
        }
        TacInstruction::Jump { target } => format!("  br label %{}\n", target),
        TacInstruction::JumpIfZero { condition, target } => {
            let (load, v, ty) = load_val(condition, reg_counter);
            let r = fresh_reg(reg_counter);
            let cont = format!("cont{}", reg_counter);

            format!(
                "{}  {} = icmp eq {} {}, 0\n  br i1 {}, label %{}, label %{}\n{}:\n",
                load, r, ty, v, r, target, cont, cont
            )
        }
        TacInstruction::JumpIfNotZero { condition, target } => {
            let (load, v, ty) = load_val(condition, reg_counter);
            let r = fresh_reg(reg_counter);
            let cont = format!("cont{}", reg_counter);

            format!(
                "{}  {} = icmp ne {} {}, 0\n  br i1 {}, label %{}, label %{}\n{}:\n",
                load, r, ty, v, r, target, cont, cont
            )
        }
        TacInstruction::FunCall {
            fun_name,
            args,
            dest,
        } => {
            if !defined.contains(fun_name) {
                externs.insert(fun_name.clone());
            }

            let mut ir = String::new();
            let mut arg_list = vec![];

            for a in args {
                let (load, v, ty) = load_val(a, reg_counter);
                ir.push_str(&load);
                arg_list.push(format!("{} {}", ty, v));
            }

            match dest {
                TacVal::Var(_, Type::Unit) => {
                    ir.push_str(&format!(
                        "  call void @{}({})\n",
                        fun_name,
                        arg_list.join(", ")
                    ));
                }
                TacVal::Var(name, ty) => {
                    let r = fresh_reg(reg_counter);
                    let llvm_ty = llvm_type(ty);

                    ir.push_str(&format!(
                        "  {} = call {} @{}({})\n  store {} {}, {}* %{}\n",
                        r,
                        llvm_ty,
                        fun_name,
                        arg_list.join(", "),
                        llvm_ty,
                        r,
                        llvm_ty,
                        name
                    ));
                }
                _ => unreachable!(),
            }

            ir
        }
        TacInstruction::Label(_) => unreachable!(),
        TacInstruction::Truncate { src, dest } => {
            let (load, v, src_ty) = load_val(src, reg_counter);
            let dst_ty = llvm_type(match dest {
                TacVal::Var(_, ty) => ty,
                _ => unreachable!(),
            });

            let r = fresh_reg(reg_counter);

            format!(
                "{}  {} = trunc {} {} to {}\n  store {} {}, {}* %{}\n",
                load,
                r,
                src_ty,
                v,
                dst_ty,
                dst_ty,
                r,
                dst_ty,
                var_name(dest)
            )
        }
        TacInstruction::SignExtend { src, dest } => {
            let (load, v, src_ty) = load_val(src, reg_counter);
            let dst_ty = llvm_type(match dest {
                TacVal::Var(_, ty) => ty,
                _ => unreachable!(),
            });

            let r = fresh_reg(reg_counter);

            format!(
                "{}  {} = sext {} {} to {}\n  store {} {}, {}* %{}\n",
                load,
                r,
                src_ty,
                v,
                dst_ty,
                dst_ty,
                r,
                dst_ty,
                var_name(dest)
            )
        }
        TacInstruction::F64ToI32 { src, dest } => {
            let (load, v, _) = load_val(src, reg_counter);
            let r = fresh_reg(reg_counter);

            format!(
                "{}  {} = fptosi double {} to i32\n  store i32 {}, i32* %{}\n",
                load,
                r,
                v,
                r,
                var_name(dest)
            )
        }

        TacInstruction::F64ToI64 { src, dest } => {
            let (load, v, _) = load_val(src, reg_counter);
            let r = fresh_reg(reg_counter);

            format!(
                "{}  {} = fptosi double {} to i64\n  store i64 {}, i64* %{}\n",
                load,
                r,
                v,
                r,
                var_name(dest)
            )
        }

        TacInstruction::I32ToF64 { src, dest } => {
            let (load, v, _) = load_val(src, reg_counter);
            let r = fresh_reg(reg_counter);

            format!(
                "{}  {} = sitofp i32 {} to double\n  store double {}, double* %{}\n",
                load,
                r,
                v,
                r,
                var_name(dest)
            )
        }

        TacInstruction::I64ToF64 { src, dest } => {
            let (load, v, _) = load_val(src, reg_counter);
            let r = fresh_reg(reg_counter);

            format!(
                "{}  {} = sitofp i64 {} to double\n  store double {}, double* %{}\n",
                load,
                r,
                v,
                r,
                var_name(dest)
            )
        }
    }
}

fn load_val(v: &TacVal, reg_counter: &mut usize) -> (String, String, &'static str) {
    match v {
        TacVal::Constant(TacConst::I32(c)) => ("".into(), c.to_string(), "i32"),
        TacVal::Constant(TacConst::I64(c)) => ("".into(), c.to_string(), "i64"),
        TacVal::Constant(TacConst::F64(c)) => ("".into(), format!("{:.6e}", c), "double"),

        TacVal::Var(_, Type::Unit) => ("".into(), "".into(), "void"),

        TacVal::Var(name, ty) => {
            let r = fresh_reg(reg_counter);
            let llvm_ty = llvm_type(ty);
            (
                format!("  {} = load {}, {}* %{}\n", r, llvm_ty, llvm_ty, name),
                r,
                llvm_ty,
            )
        }
    }
}

fn llvm_type(ty: &Type) -> &'static str {
    match ty {
        Type::I32 => "i32",
        Type::I64 => "i64",
        Type::F64 => "double",
        Type::Unit => "void",
        Type::FunType { .. } => unreachable!("function types not first-class in LLVM IR here"),
    }
}

fn fresh_reg(reg_counter: &mut usize) -> String {
    let r = format!("%r{}", *reg_counter);
    *reg_counter += 1;
    r
}

fn var_name(v: &TacVal) -> &str {
    match v {
        TacVal::Var(name, _) => name,
        _ => panic!("expected variable"),
    }
}

fn collect_locals(body: &[TacInstruction], params: &[String]) -> HashSet<(String, Type)> {
    let mut vars = HashSet::new();

    for p in params {
        vars.insert((p.clone(), Type::I32));
    }

    for instr in body {
        match instr {
            TacInstruction::Copy { src, dest } | TacInstruction::Unary { src, dest, .. } => {
                collect_val(src, &mut vars);
                collect_val(dest, &mut vars);
            }

            TacInstruction::Binary {
                src1, src2, dest, ..
            } => {
                collect_val(src1, &mut vars);
                collect_val(src2, &mut vars);
                collect_val(dest, &mut vars);
            }

            TacInstruction::FunCall { args, dest, .. } => {
                for a in args {
                    collect_val(a, &mut vars);
                }
                collect_val(dest, &mut vars);
            }

            TacInstruction::Truncate { src, dest } | TacInstruction::SignExtend { src, dest } => {
                collect_val(src, &mut vars);
                collect_val(dest, &mut vars);
            }

            TacInstruction::Return(None) => (),
            TacInstruction::JumpIfZero { condition: v, .. }
            | TacInstruction::JumpIfNotZero { condition: v, .. } => {
                collect_val(v, &mut vars);
            }

            _ => {}
        }
    }

    vars
}

fn collect_val(v: &TacVal, vars: &mut HashSet<(String, Type)>) {
    if let TacVal::Var(name, ty) = v {
        vars.insert((name.clone(), ty.clone()));
    }
}
