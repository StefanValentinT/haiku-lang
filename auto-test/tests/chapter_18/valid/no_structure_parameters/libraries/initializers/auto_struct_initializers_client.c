/* Test initialization of non-nested structs with automatic storage duration,
 * including:
 * - partial initialization
 * - implicit type conversions
 * - compound and single expressions as initializers
 * - string literals as pointer and array initializers
 * */



double get_double(void) {
    return 2e12;
}


int test_full_initialization(void) {
    struct s full = {
        
        "I'm a struct!", "sup",
        &full,          
        get_double(),   
        &(full.four_d)  
                        
    };

    return validate_full_initialization(&full);
}


int test_partial_initialization(void) {
    static char *msg = "Another string literal";
    struct s partial = {
        msg,         
        {'a', 'b'},  
        (struct s *)calloc(
            1,
            sizeof(struct s))  
        
    };

    return validate_partial_initialization(&partial, msg);
}


int test_implicit_type_conversions(void) {
    static int i = 3000;

    struct s converted = {
        malloc(5),              
        {i / 2, i / 3, i * 4},  
        0l,                     
        i - 1,                  
        calloc(1, sizeof(double))  
    };

    return validate_converted(&converted);
}


int test_single_exp_initializer(void) {
    double d = 123.4;
    struct s s1 = {"Yet another string", "xy", &s1, 150.0, &d};
    struct s s2 = s1;

    return validate_two_structs(&s1, &s2);
}

int main(void) {
    if (!test_full_initialization()) {
        return 1;
    }

    if (!test_partial_initialization()) {
        return 2;
    }

    if (!test_implicit_type_conversions()) {
        return 3;
    }

    if (!test_single_exp_initializer()) {
        return 4;
    }

    return 0;  
}