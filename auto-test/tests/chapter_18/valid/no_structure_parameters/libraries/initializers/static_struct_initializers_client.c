/* Test initialization of non-nested static structs, including:
 * - partial initialization
 * - implicit conversion of scalar elements
 * - array decay of string literals
 */




struct s uninitialized;


struct s partial = {1.0, "Hello"};


struct s partial_with_array = {3.0, "!", {1}, 2};


struct s converted = {
    1152921504606846977l,  
    0l,                    
    "abc",                 
    17179869189l           
};

int main(void) {
    if (!test_uninitialized()) {
        return 1;
    }

    if (!test_partially_initialized()) {
        return 2;
    }

    if (!test_partial_inner_init()) {
        return 3;
    }

    if (!test_implicit_conversion()) {
        return 4;
    }

    return 0;  
}
