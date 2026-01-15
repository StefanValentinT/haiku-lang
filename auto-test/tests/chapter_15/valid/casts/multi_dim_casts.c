/* Test that we can cast to pointers to different dimensions in a multi-dimensional array */

int main(void) {
    int multi_dim[2][3] = {{0, 1, 2}, {3, 4, 5}};

    
    int (*array_pointer)[2][3] = &multi_dim;

    
    int (*row_pointer)[3] = (int (*)[3]) array_pointer;

    if (row_pointer != multi_dim) {
        return 1;
    }

    
    row_pointer = row_pointer + 1;
    if (row_pointer[0][1] != 4) {
        return 2;
    }

    
    int *elem_ptr = (int *) row_pointer;

    if (*elem_ptr != 3 ){
        return 3;
    }

    elem_ptr = elem_ptr + 2;
    if (*elem_ptr != 5) {
        return 4;
    }

    
    
    row_pointer = row_pointer - 1;
    if ((int (*)[2][3]) row_pointer != array_pointer) {
        return 5;
    }

    return 0;
}