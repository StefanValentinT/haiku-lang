
int main(void) {
    long arr[2][3][4] = {
        {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
        {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}}};

    
    long (*outer_ptr)[3][4] = arr + 1;
    if (outer_ptr-- != &arr[1]) {
        return 1; 
    }
    if (outer_ptr[0][1] != arr[0][1]) {
        return 2; 
    }

    if ((++outer_ptr)[0][2][3] != 24) {
        return 3; 
    }
    if (outer_ptr[0][2][3] != 24) {
        return 4; 
    }

    
    long (*inner_ptr)[4] = arr[0] + 1;
    if (inner_ptr++[0][2] != 7) {
        return 5; 
    }

    if (inner_ptr[0][2] != 11) {
        return 6; 
    }

    if ((--inner_ptr)[0][1] != 6) {
        return 7; 
    }

    
    long *scalar_ptr = arr[1][2];
    if (scalar_ptr--[2] != 23) {
        return 8; 
    }
    if (scalar_ptr[2] != 22) {
        return 9; 
    }

    return 0;  
}