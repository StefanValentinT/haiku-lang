


struct has_char_array {
    char arr[8];
};

union has_array {
    long l;
    struct has_char_array s;
};

int get_flag(void) {
    static int flag = 0;
    flag = !flag;
    return flag;
}

int main(void) {
    union has_array union1 = {9876543210l};
    union has_array union2 = {1234567890l};

    
    if ((get_flag() ? union1 : union2).s.arr[0] != -22) {
        return 1; 
    }

    
    if ((get_flag() ? union1 : union2).s.arr[0] != -46) {
        return 2; 
    }

    return 0; 
}