/* Get the addresses of structure members to validate their offset and alignment
 * (including nested members accessed through chains of . and -> operations)
 * and addresses of one-past-the-end of structs to validate trailing padding
 * */

void *malloc(unsigned long size);



int test_eightbytes(void) {
    struct eight_bytes s;
    unsigned long start_addr = (unsigned long)&s;
    unsigned long i_addr = (unsigned long)&s.i;
    unsigned long c_addr = (unsigned long)&s.c;
    unsigned long end_addr = (unsigned long)(&s + 1);

    
    if (start_addr % 4 != 0) {
        return 0;
    }

    
    if (start_addr != i_addr) {
        return 0;
    }

    
    if (c_addr - start_addr != 4) {
        return 0;
    }

    
    if (end_addr - start_addr != 8) {
        return 0;
    }

    return 1;  
}



int test_internal_padding(void) {
    struct internal_padding *s_ptr = malloc(sizeof(struct internal_padding));
    unsigned long start_addr = (unsigned long)s_ptr;
    unsigned long c_addr = (unsigned long)&s_ptr->c;
    unsigned long d_addr = (unsigned long)&s_ptr->d;
    unsigned long end_ptr = (unsigned long)(s_ptr + 1);

    
    if (start_addr % 8 != 0) {
        return 0;
    }

    
    if (start_addr != c_addr) {
        return 0;
    }

    
    if (d_addr - c_addr != 8) {
        return 0;
    }

    
    if (end_ptr - start_addr != 16) {
        return 0;
    }

    return 1;  
}



int test_three_bytes(void) {
    
    
    static struct three_bytes s;

    unsigned long start_addr = (unsigned long)&s;
    unsigned long arr_addr = (unsigned long)&s.arr;
    unsigned long arr0_addr = (unsigned long)&s.arr[0];
    unsigned long arr1_addr = (unsigned long)&s.arr[1];
    
    unsigned long arr1_addr_alt = (unsigned long)(s.arr + 1);
    unsigned long arr2_addr = (unsigned long)&s.arr[2];
    unsigned long arr_end = (unsigned long)(&s.arr + 1);
    unsigned long struct_end = (unsigned long)(&s + 1);

    
    if (start_addr != arr_addr) {
        return 0;
    }

    if (start_addr != arr0_addr) {
        return 0;
    }

    
    if (arr1_addr - start_addr != 1) {
        return 0;
    }

    if (arr1_addr != arr1_addr_alt) {
        return 0;
    }

    if (arr2_addr - start_addr != 2) {
        return 0;
    }

    
    if (arr_end - start_addr != 3) {
        return 0;
    }

    if (struct_end - start_addr != 3) {
        return 0;
    }

    return 1;  
}




int test_sixteen_bytes(void) {
    static struct sixteen_bytes s;
    struct sixteen_bytes *s_ptr = &s;

    
    unsigned long start_addr = (unsigned long)s_ptr;
    unsigned long eight_addr = (unsigned long)&s_ptr->eight;
    unsigned long eight_i_addr = (unsigned long)&s_ptr->eight.i;
    unsigned long eight_c_addr = (unsigned long)&s_ptr->eight.c;
    unsigned long two = (unsigned long)&s_ptr->two;
    unsigned long two_arr = (unsigned long)s_ptr->two.arr;
    unsigned long two_arr0 = (unsigned long)&s_ptr->two.arr[0];
    unsigned long two_arr1 = (unsigned long)&s_ptr->two.arr[1];
    unsigned long two_arr_end = (unsigned long)(&s_ptr->two.arr + 1);
    unsigned long two_end = (unsigned long)(&s_ptr->two + 1);
    unsigned long three = (unsigned long)&s_ptr->three;
    
    
    unsigned long three_end = (unsigned long)(&s_ptr->three + 1);
    unsigned long struct_end = (unsigned long)(s_ptr + 1);

    
    if (start_addr % 4 != 0) {
        return 0;
    }

    
    if (start_addr != eight_addr) {
        return 0;
    }

    if (start_addr != eight_i_addr) {
        return 0;
    }

    if (eight_c_addr - start_addr != 4) {
        return 0;
    }

    
    if (two - start_addr != 8) {
        return 0;
    }

    if (two_arr - start_addr != 8) {
        return 0;
    }

    if (two_arr0 - start_addr != 8) {
        return 0;
    }

    
    if (two_arr1 - start_addr != 9) {
        return 0;
    }

    
    if (two_arr_end - start_addr != 10) {
        return 0;
    }

    if (two_arr_end != two_end) {
        return 0;
    }

    if (three - start_addr != 10) {
        return 0;
    }

    if (three_end - start_addr != 13) {
        return 0;
    }

    if (struct_end - start_addr != 16) {
        return 0;
    }

    
    

    unsigned long eight_i_addr_alt = (unsigned long)&s.eight.i;
    unsigned long eight_c_addr_alt = (unsigned long)&s.eight.c;
    unsigned long two_arr_alt = (unsigned long)s.two.arr;
    unsigned long two_arr1_alt = (unsigned long)&s.two.arr[1];
    unsigned long three_alt = (unsigned long)&s.three;

    if (eight_i_addr_alt != eight_i_addr) {
        return 0;
    }

    if (eight_c_addr_alt != eight_c_addr) {
        return 0;
    }

    if (two_arr_alt != two_arr) {
        return 0;
    }

    if (two_arr1_alt != two_arr1) {
        return 0;
    }

    if (three_alt != three) {
        return 0;
    }

    return 1;  
}



int test_wonky_array(void) {
    struct wonky wonky_array[5];
    unsigned long array_start = (unsigned long)wonky_array;
    unsigned long elem3 = (unsigned long)(wonky_array + 3);
    unsigned long elem3_arr = (unsigned long)wonky_array[3].arr;
    unsigned long elem2_arr2 = (unsigned long)&wonky_array[2].arr[2];
    unsigned long elem2_arr_end = (unsigned long)(wonky_array[2].arr + 19);
    unsigned long elem4_arr_end = (unsigned long)(wonky_array[4].arr + 19);
    unsigned long array_end = (unsigned long)(wonky_array + 5);

    if (elem3 - array_start != 19 * 3) {
        return 0;
    }

    if (elem3_arr != elem3) {
        return 0;
    }

    if (elem2_arr2 - array_start != 19 * 2 + 2) {
        return 0;
    }

    
    if (elem2_arr_end != elem3) {
        return 0;
    }

    
    if (elem4_arr_end != array_end) {
        return 0;
    }

    return 1;  
}




int test_contains_struct_array_array(void) {
    struct contains_struct_array arr[3];
    unsigned long array_start = (unsigned long)arr;
    unsigned long first_scalar_elem = (unsigned long)(&arr[0].c);

    
    unsigned long outer0_inner0_i = (unsigned long)(&arr[0].struct_array->i);

    
    unsigned long outer0_inner0_c = (unsigned long)(&arr->struct_array->c);

    
    unsigned long outer0_end = (unsigned long)(arr->struct_array + 3);

    
    
    unsigned long outer1 = (unsigned long)(&arr[1]);

    
    unsigned long outer1_arr = (unsigned long)(arr[1].struct_array);

    
    unsigned long outer1_inner1_i =
        (unsigned long)&(((arr + 1)->struct_array + 1)->i);

    
    unsigned long outer2_inner0_c =
        (unsigned long)&((arr + 2)->struct_array->c);

    
    if (array_start % 4 != 0) {
        return 0;
    }

    
    if (first_scalar_elem != array_start) {
        return 0;
    }

    
    
    if (outer0_inner0_i - array_start != 4) {
        return 0;
    }

    
    
    if (outer0_inner0_c - array_start != 8) {
        return 0;
    }

    
    if (outer0_end != outer1) {
        return 0;
    }

    
    if (outer1_arr - array_start != 32) {
        return 0;
    }

    if (outer1_arr - outer1 != 4) {
        return 0;
    }

    
    
    
    
    
    if (outer1_inner1_i - array_start != 40) {
        return 0;
    }

    
    
    
    
    
    if (outer2_inner0_c - array_start != 64) {
        return 0;
    }

    return 1;  
}

int main(void) {
    if (!test_eightbytes()) {
        return 1;
    }

    if (!test_internal_padding()) {
        return 2;
    }

    if (!test_three_bytes()) {
        return 3;
    }

    if (!test_sixteen_bytes()) {
        return 4;
    }

    if (!test_wonky_array()) {
        return 5;
    }

    if (!test_contains_struct_array_array()) {
        return 6;
    }

    return 0;  
}