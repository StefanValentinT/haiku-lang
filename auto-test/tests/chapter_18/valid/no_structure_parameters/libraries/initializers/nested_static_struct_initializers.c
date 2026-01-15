/* Test initialization of nested static structs, including:
 * - partial initialization
 * - arrays of structs, structs containing arrays
 * - implicit conversion of scalar elements, array decay of string literals
 */







int test_uninitialized(void) {
    
    if (all_zeros.one_l || all_zeros.three_msg || all_zeros.four_d) {
        return 0;
    }

    
    if (all_zeros.two_struct.one_i || all_zeros.two_struct.two_arr[0] ||
        all_zeros.two_struct.two_arr[1] || all_zeros.two_struct.two_arr[2] ||
        all_zeros.two_struct.three_u) {
        return 0;
    }

    return 1;  
}


/*
    struct outer partial = {
        100l,
        {10, {10}},  
        "Hello!"};   
*/
int test_partially_initialized(void) {
    
    if (partial.one_l != 100l || strcmp(partial.three_msg, "Hello!")) {
        return 0;
    }

    if (partial.four_d) {  
        return 0;
    }

    
    if (partial.two_struct.one_i != 10 || partial.two_struct.two_arr[0] != 10) {
        return 0;
    }

    if (partial.two_struct.two_arr[1] || partial.two_struct.two_arr[2] ||
        partial.two_struct
            .three_u) {  
        return 0;
    }

    return 1;  
}


/*
    struct outer full = {
        18014398509481979l,
        {1000, "ok",
        4292870144u},  
        "Another message",
        2e12};
*/
int test_fully_intialized(void) {
    
    if (full.one_l != 18014398509481979l ||
        strcmp(full.three_msg, "Another message") || full.four_d != 2e12) {
        return 0;
    }

    
    if (full.two_struct.one_i != 1000 || full.two_struct.two_arr[0] != 'o' ||
        full.two_struct.two_arr[1] != 'k' || full.two_struct.two_arr[2] != 0 ||
        full.two_struct.three_u != 4292870144u) {
        return 0;
    }

    return 1;  
}


/*
    struct outer converted = {
        10.5,  
        {
            2147483650u,  
            {
                15.6,             
                17592186044419l,  
                2147483777u       
            },
            1152921506754330624ul  
        },
        0ul,                   
        9223372036854776833ul  
    };
*/
int test_implicit_conversions(void) {
    
    if (converted.one_l != 10l || converted.three_msg != 0 ||
        converted.four_d != 9223372036854777856.0) {
        return 0;
    }

    
    if (converted.two_struct.one_i != -2147483646 ||
        converted.two_struct.two_arr[0] != 15 ||
        converted.two_struct.two_arr[1] != 3 ||
        converted.two_struct.two_arr[2] != -127 ||
        converted.two_struct.three_u != 2147483648u) {
        return 0;
    }

    return 1;  
}


/*
    struct outer struct_array[3] = {{1, {2, "ab", 3}, 0, 5},
                                        {6, {7, "cd", 8}, "Message", 9}};
*/
int test_array_of_structs(void) {
    

    
    if (struct_array[0].one_l != 1 || struct_array[0].three_msg != 0 ||
        struct_array[0].four_d != 5) {
        return 0;
    }

    
    if (struct_array[0].two_struct.one_i != 2 ||
        strcmp((char *)struct_array[0].two_struct.two_arr, "ab") ||
        struct_array[0].two_struct.three_u != 3) {
        return 0;
    }

    
    if (struct_array[1].one_l != 6 ||
        strcmp((char *)struct_array[1].three_msg, "Message") ||
        struct_array[1].four_d != 9) {
        return 0;
    }

    
    if (struct_array[1].two_struct.one_i != 7 ||
        strcmp((char *)struct_array[1].two_struct.two_arr, "cd") ||
        struct_array[1].two_struct.three_u != 8) {
        return 0;
    }

    
    if (struct_array[2].one_l || struct_array[2].three_msg ||
        struct_array[2].four_d) {
        return 0;
    }

    
    if (struct_array[2].two_struct.one_i ||
        struct_array[2].two_struct.two_arr[0] ||
        struct_array[2].two_struct.two_arr[1] ||
        struct_array[2].two_struct.two_arr[2] ||
        struct_array[2].two_struct.three_u) {
        return 0;
    }

    return 1;  
}
