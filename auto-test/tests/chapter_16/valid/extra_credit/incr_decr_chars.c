
int main(void) {
    static char chars[5] = {123, 124, 125, 126, 127};
    if (chars[0]++ != 123) {
        return 1;  
    }

    if (chars[1]-- != 124) {
        return 2;  
    }

    if (++chars[2] != 126) {
        return 3;  
    }

    if (--chars[3] != 125) {
        return 4;  
    }

    
    
    
    if (++chars[4] != -128) {
        return 5;  
    }

    
    if (chars[0] != 124) {
        return 6;  
    }

    if (chars[1] != 123) {
        return 7;  
    }
    if (chars[2] != 126) {
        return 8;  
    }
    if (chars[3] != 125) {
        return 9;  
    }
    if (chars[4] != -128) {
        return 10;  
    }

    
    signed char c = -128;
    c--;
    if (c != 127) {
        return 11;  
    }

    return 0;  
}