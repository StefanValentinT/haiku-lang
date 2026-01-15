



int main(void) {
    long long_arr[2] = {1, 2};
    static int i = 3;
    static unsigned char uc = 4;
    double d = 5.0;
    long *ptr = long_arr;

    if (sizeof(long_arr[1] *= 10) != 8) {
        return 1;  
    }
    if (sizeof(i /= 10ul) != 4) {
        return 2;  
    }
    if (sizeof(uc %= 2) != 1) {
        return 3;  
    }
    if (sizeof(d -= 11) != 8) {
        return 4;  
    }
    if (sizeof(ptr += 1) != 8) {
        return 5;  
    }

    
    if (long_arr[0] != 1) {
        return 6;  
    }
    if (long_arr[1] != 2) {
        return 7;  
    }
    if (i != 3) {
        return 8;  
    }
    if (uc != 4) {
        return 9;  
    }
    if (d != 5.0) {
        return 10;  
    }
    if (ptr != long_arr) {
        return 11;  
    }

    return 0;  
}