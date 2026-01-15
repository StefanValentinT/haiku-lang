#[macro_export]
macro_rules! pipe {
    ($init:tt $(=>$fn:ident)+) => {{
        let mut r = $init;
        $( r = $fn(r); )*
        r
    }}
}
