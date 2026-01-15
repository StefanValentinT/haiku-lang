/* Test that arrays don't decay to pointers
 * when they're the operands of sizeof expression */


unsigned long sizeof_adjusted_param(int arr[3]) {
    
    
    return sizeof arr;
}

int main(void) {
    
    int arr[3];
    if (sizeof arr != 12) {
        return 1;
    }

    static long nested_arr[4][5];

    
    if (sizeof nested_arr[2] != 40) {
        return 2;
    }

    
    if (sizeof "Hello, World!" != 14) {
        return 3;
    }

    
    
    if (sizeof_adjusted_param(arr) != 8) {
        return 4;
    }

    return 0;
}