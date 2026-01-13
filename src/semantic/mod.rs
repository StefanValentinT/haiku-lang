mod identifier_resolution;
mod loop_labeling;
mod typecheck;

use crate::{
    parser::Program,
    pipe,
    semantic::{
        identifier_resolution::identifier_resolution_pass, loop_labeling::loop_labeling_pass,
        typecheck::type_check,
    },
};

pub fn semantic_analysis(program: Program) -> Program {
    pipe!(program => identifier_resolution_pass  => type_check => loop_labeling_pass)
}
