use crate::ast::ast_type::Type;
use crate::ast::typed_ast::TypedFunDecl;
use std::collections::HashMap;

pub fn builtin_functions() -> HashMap<String, TypedFunDecl> {
    let mut map = HashMap::new();

    map.insert(
        "print".to_string(),
        TypedFunDecl {
            name: "print".to_string(),
            params: vec![(
                "s".to_string(),
                Type::Slice {
                    element_type: Box::new(Type::Char),
                },
            )],
            ret_type: Type::I32,
            body: None,
        },
    );

    map
}
