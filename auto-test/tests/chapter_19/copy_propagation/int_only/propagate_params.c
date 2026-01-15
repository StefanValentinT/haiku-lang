/* Test that we can propagate copies both to and from function parameters;
 * similar to propagate_var, but with paramters instead of variables.
 * */
int callee(int a, int b) {
    return a * b;
}
int f(void) {
    return 3;
}
int globl = 0;
int set_globvar(void) {
    globl = 4;
    return 0;
}
int target(int a, int b) {
    b = a;  

    
    
    
    set_globvar();
    
    int product = callee(a, b);

    
    
    
    b = f();
    return (product + a - b);  
}

int main(void) {
    if (target(5, 6) != 27) {
        return 1;
    }

    
    if (globl != 4) {
        return 2;
    }

    return 0;  
}