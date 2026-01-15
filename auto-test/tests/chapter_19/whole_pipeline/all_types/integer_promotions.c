/* Make sure we promote characters to integers before constant folding */

int target(void) {
    char c1 = 120;
    char c2 = 3;
    
    
    
    char c3 = (c1 + c1) / c2;

    unsigned char uc1 = 200;
    unsigned char uc2 = 12;
    
    
    unsigned char uc3 = (uc1 + uc1) / uc2;
    if (c3 != 80) {
        return 1; 
    }
    if (uc3 != 33) {
        return 2; 
    }
    return 0;
}

int main(void) {
    return target();
}