/* Test that we correctly propagate copies into type conversion instructions */

int target(void) {
    unsigned char uc = 250;
    int i = uc * 2;              
    double d = i * 1000.;        
    unsigned long ul = d / 6.0;  
    d = ul + 5.0;                
    long l = -i;                 
    char c = l;                  
    return d + i - c;            
}

int main(void) {
    if (target() != 83826) {
        return 1; 
    }
    return 0; 
}