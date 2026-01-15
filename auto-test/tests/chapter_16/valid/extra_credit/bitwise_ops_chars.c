


int main(void) {
    unsigned char uc = 135;
    char c = -116;
    
    
    
    if ((uc & c) != 132) {
        return 1;  
    }

    
    
    
    if ((uc | c) != -113) {
        return 2;  
    }

    
    
    
    if (((c ^ 1001u) | 360l) != 4294966637) {
        return 3; 
    }

    return 0;
}