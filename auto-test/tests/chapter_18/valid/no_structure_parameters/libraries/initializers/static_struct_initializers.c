/* Test initialization of non-nested static structs, including:
 * - partial initialization
 * - implicit conversion of scalar elements
 * - array decay of string literals
 */







int test_uninitialized(void) {
    
    if (uninitialized.one_d || uninitialized.two_msg ||
        uninitialized.three_arr[0] || uninitialized.three_arr[1] ||
        uninitialized.three_arr[2] || uninitialized.four_i) {
        return 0;
    }
    return 1;  
}



int test_partially_initialized(void) {
    
    if (partial.one_d != 1.0 || strcmp(partial.two_msg, "Hello")) {
        return 0;
    }

    
    if (partial.three_arr[0] || partial.three_arr[1] || partial.three_arr[2] ||
        partial.four_i) {
        return 0;
    }

    return 1;  
}



int test_partial_inner_init(void) {
    
    if (partial_with_array.one_d != 3.0 ||
        strcmp(partial_with_array.two_msg, "!") ||
        partial_with_array.three_arr[0] != 1 ||
        partial_with_array.four_i != 2) {
        return 0;
    }

    
    if (partial_with_array.three_arr[1] || partial_with_array.three_arr[2]) {
        return 0;
    }

    return 1;  
}


/*
    struct s converted = {
        1152921504606846977l,  
        0l,                   
        "abc",                
        17179869189l          
    };
*/
int test_implicit_conversion(void) {
    
    if (converted.one_d != 1152921504606846976.0 || converted.two_msg ||
        converted.three_arr[0] != 'a' || converted.three_arr[1] != 'b' ||
        converted.three_arr[2] != 'c' || converted.four_i != 5) {
        return 0;
    }

    return 1;  
}