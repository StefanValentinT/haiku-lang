
int main(void) {
    unsigned char chars[5] = {0, 2, 4, 253, 255};

    
    if (chars[0]--) {  
        return 1;      
    }

    if (chars[1]++ != 2) {
        return 2;  
    }

    if (--chars[3] != 252) {
        return 3;
    }

    if (++chars[4] != 0) {  
        return 4;
    }

    
    if (chars[0] != 255) {  
        return 5;
    }

    if (chars[1] != 3) {
        return 6;
    }

    if (chars[2] != 4) {  
        return 7;
    }

    if (chars[3] != 252) {
        return 8;
    }

    if (chars[4]) {
        return 9;
    }

    return 0;  
}