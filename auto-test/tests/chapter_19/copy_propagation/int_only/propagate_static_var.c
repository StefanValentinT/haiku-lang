/* Propagate a copy where the source value is a variable with static storage
 * duration, in a function with no control flow strucures.
 * */
int callee(int a, int b) {
    return a + b;
}

int target(void) {
    static int x = 3;

    
    
    
    
    static int y = 0;

    y = x;  

    
    int sum = callee(x, y);

    
    
    
    x = x + 1;
    return sum;
}

int main(void) {
    
    if (target() != 6) {
        return 1;
    }
    
    if (target() != 8) {
        return 2;
    }
    return 0;  
}
