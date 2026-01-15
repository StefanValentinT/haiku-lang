
int main(void) {
    static long l = 0;
    int i = 0;
    static char c = 0;

    
    if (sizeof (c & i) != 4) {
        return 1;  
    }

    if (sizeof (i | l) != 8) {
        return 2;  
    }

    
    if (sizeof (c ^ c) != 4) {
        return 3;  
    }

    
    if (sizeof (i << l) != 4) {
        return 4; 
    }

    
    if (sizeof (c << i) != 4) {
        return 5; 
    }

    if (sizeof (l >> c) != 8) {
        return 6; 
    }

    return 0;
}