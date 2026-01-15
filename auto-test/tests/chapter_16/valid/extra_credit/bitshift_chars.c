




int main(void) {
    unsigned char uc = 255;

    
    
    
   

    
    if ((uc >> 3) != 31) {
        return 2; 
    }

    signed char sc = -127;
    char c = 5;
    
    if ((sc >> c) != -4) {
        return 3;  
    }

    
    if (((-(c << 3ul)) >> 3) != -5) {
        return 4;  
    }

    
    if ((-(uc << 5u) >> 5u) != -255l) {
        return 5; 
    }

    return 0; 

}