
int main(void) {
    unsigned int i = 0;

    
    if (i-- != 0) {
        return 1;
    }
    if (i != 4294967295U) { 
        return 2;
    }

    
    if (--i != 4294967294U) {
        return 3;
    }
    if (i != 4294967294U) {
        return 4;
    }

    unsigned long l = 18446744073709551614UL;
    
    if (l++ != 18446744073709551614UL) {
        return 5;
    }
    if (l != 18446744073709551615UL) {
        return 6;
    }
    if (++l != 0) { 
        return 7;
    }
    if (l != 0) {
        return 8;
    }
    return 0; 
}