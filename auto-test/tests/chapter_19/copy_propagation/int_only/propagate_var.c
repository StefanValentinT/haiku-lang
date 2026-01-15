/* Test that we can propagate copies where the source value is
 * a variable, in a function with no control flow strucures.
 * */
int callee(int a, int b) {
    return a + b;
}
int f(void) {
    return 3;
}

int globl = 0;
int set_globvar(void) {
    globl = 4;
    return 0;
}

int target(void) {
    int x = f();
    int y = x;  

    
    
    
    set_globvar();

    
    int sum = callee(x, y);

    
    
    
    y = f();
    return (sum + x * y);  
}

int main(void) {
    
    if (target() != 15) {
        return 1;
    }

    
    if (globl != 4) {
        return 2;
    }
    return 0;  
}
