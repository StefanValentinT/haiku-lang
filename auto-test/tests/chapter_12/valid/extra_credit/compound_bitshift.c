int main(void) {

    
    int i = -2;
    
    
    i >>= 3u;
    if (i != -1) {
        return 1;
    }

    unsigned long ul = 18446744073709551615UL;  
    ul <<= 44;                                  
    if (ul != 18446726481523507200ul) {
        return 2;  
    }
    return 0;  
}