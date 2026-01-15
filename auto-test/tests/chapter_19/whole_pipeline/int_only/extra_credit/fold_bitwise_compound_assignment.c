/* Test that we can evaluate bitwise compound assignment expressions at compile time */

int target(void) {
    int v = -100;
    int w = 100;
    int x = 200;
    int y = 300;
    int z = 40000;

    v ^= 10; 
    w |= v; 
    x &= 30; 
    y <<= x; 
    
    z >>= (x |= 2); 

    if (v == -106 && w == -10 && x == 10 && y == 76800 && z == 39) {
        return 0; 
    }

    return 1; 
}

int main(void) {
    return target();
}