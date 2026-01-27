use crate::ast::typed_ast::{TypedFunDecl, TypedProgram};

pub fn perform_ctfe_pass(program: TypedProgram) -> Result<TypedProgram, String> {
    let result = program;
    Ok(result)
}

pub fn is_compile_time_function(func: &TypedFunDecl) -> bool {
    matches!(func.exec_time, crate::ast::ast_type::ExecTime::CompileTime)
}
