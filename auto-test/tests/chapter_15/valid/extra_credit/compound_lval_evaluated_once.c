

int get_call_count(void) {
    
    
    static int count = 0;
    count += 1;
    return count;
}

int main(void) {
    int arr[4] = {10, 11, 12, 13};
    if (arr[get_call_count()] != 11) { 
        return 1; 
    }
    int *end_ptr = arr + 4;
    if ((end_ptr - 1)[-get_call_count()] != 11) { 
        return 2; 
    }

    if (get_call_count() != 3) {
        return 3; 
    }

    return 0; 
}