


static long nested_arr[3][4][5] = {{{10, 9, 8}, {1, 2}}, {{100, 99, 98}}};

int main(void) {
    
    long(*outer_ptr)[4][5] = nested_arr;
    outer_ptr += 1;
    if (outer_ptr != nested_arr + 1) {
        return 1;  
    }
    if (outer_ptr[0][0][0] != 100) {
        return 2;
    }

    long(*inner_ptr)[5] =
        nested_arr[0] + 4;  
    inner_ptr -= 3;
    if (inner_ptr[0][1] != 2) {
        return 3;
    }

    
    unsigned long idx = nested_arr[0][0][0] - 9;  
    if ((inner_ptr += idx) != &nested_arr[0][2]) {
        return 4;
    }

    if ((inner_ptr[-2][1] != 9)) {
        return 5;
    }

    return 0;
}