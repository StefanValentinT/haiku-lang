/* Test comparison of elements of the same array, including multi-dimensional arrays */


unsigned long gt(unsigned long *a, unsigned long *b) {
    return a > b;
}


unsigned long lt(unsigned long *a, unsigned long *b) {
    return a < b;
}

unsigned long ge(unsigned long *a, unsigned long *b) {
    return a >= b;
}

unsigned long le(unsigned long *a, unsigned long *b) {
    return a <= b;
}


unsigned long gt_nested(unsigned long (*a)[5], unsigned long (*b)[5]) {
    return a > b;
}

unsigned long ge_nested(unsigned long (*a)[5], unsigned long (*b)[5]) {
    return a >= b;
}


int main(void)
{
    

    
    
    unsigned long arr[5];
    unsigned long *elem_1 = arr + 1;
    unsigned long *elem_4 = arr + 4;
    if (gt(elem_1, elem_4)) {
        return 1;
    }
    if (!(lt(elem_1, elem_4))) {
        return 2;
    }
    if (!(ge(elem_1, elem_1))) {
        return 3;
    }
    if (le(elem_4, elem_1)) {
        return 4;
    }

    
    unsigned long *one_past_the_end = arr + 5;
    if (!(gt(one_past_the_end, elem_4))) {
        return 5;
    }
    if (one_past_the_end != elem_4 + 1) {
        return 6;
    }

    
    unsigned long nested_arr[4][5];

    unsigned long *elem_3_2 = *(nested_arr + 3) + 2;
    unsigned long *elem_3_3 = *(nested_arr + 3) + 3;

    if (lt(elem_3_3, elem_3_2)) {
        return 7;
    }

    if (!ge(elem_3_3, elem_3_2)) {
        return 8;
    }

    
    unsigned long (*subarray_0)[5] = nested_arr;
    unsigned long (*subarray_3)[5] = nested_arr + 3;
    unsigned long (*subarray_one_past_the_end)[5] = nested_arr + 4;

    if (ge_nested(subarray_0, subarray_3)){
        return 9;
    }

    if (!(gt_nested(subarray_one_past_the_end, subarray_3))) {
        return 10;
    }

    if (subarray_3 != subarray_one_past_the_end - 1) {
        return 11;
    }

    return 0;
}