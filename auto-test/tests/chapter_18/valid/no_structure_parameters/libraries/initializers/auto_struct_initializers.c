/* Test initialization of non-nested structs with automatic storage duration,
 * including:
 * - partial initialization
 * - implicit type conversions
 * - compound and single expressions as initializers
 * - string literals as pointer and array initializers
 * */


int validate_full_initialization(struct s *ptr) {
    if (strcmp(ptr->one_msg, "I'm a struct!") || ptr->two_arr[0] != 's' ||
        ptr->two_arr[1] != 'u' || ptr->two_arr[2] != 'p' ||
        ptr->three_self_ptr != ptr || ptr->four_d != 2e12 ||
        *ptr->five_d_ptr != 2e12) {
        return 0;
    }

    return 1;  
}

int validate_partial_initialization(struct s *ptr, char *expected_msg) {
    if (ptr->one_msg != expected_msg || ptr->two_arr[0] != 'a' ||
        ptr->two_arr[1] != 'b') {
        return 0;
    }

    
    if (ptr->three_self_ptr->one_msg) {
        return 0;
    }

    
    if (ptr->two_arr[2] || ptr->four_d || ptr->five_d_ptr) {
        return 0;
    }

    return 1;  
}
int validate_converted(struct s *ptr) {
    if (!ptr->one_msg ||  
        ptr->two_arr[0] != 220 || ptr->two_arr[1] != 232 ||
        ptr->two_arr[2] != 224 || ptr->three_self_ptr ||
        ptr->four_d != 2999.0 || *ptr->five_d_ptr != 0.0) {
        return 0;
    }

    return 1;  
}

int validate_two_structs(struct s *ptr1, struct s *ptr2) {
    
    if (strcmp(ptr2->one_msg, "Yet another string") ||
        ptr2->one_msg != ptr1->one_msg ||  
                                           
        
        ptr2->two_arr[0] != 'x' || ptr2->two_arr[1] != 'y' ||
        ptr2->three_self_ptr !=
            ptr1 ||  
        ptr2->four_d != 150.0 ||
        *ptr1->five_d_ptr != 123.4) {
        return 0;
    }

    
    
    if (ptr1->two_arr == ptr2->two_arr) {
        return 0;
    }
    return 1;  
}