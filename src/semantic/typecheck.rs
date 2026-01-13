use crate::parser::Program;

pub fn type_check(program: Program) -> Program {
    match program {
        Program::Program(funcs) => {
            for _decl in (&funcs).into_iter() {
                // typecheck_decl(&Decl::Function(decl), &mut symbols);
            }

            Program::Program(funcs)
        }
    }
}
