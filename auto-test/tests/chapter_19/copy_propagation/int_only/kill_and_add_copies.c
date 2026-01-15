/* Test how we handle copies in the transfer function:
 * x = src should generate a copy _and_ kill previous copies
 * where x is the source or destination
 * */
static int globvar;

int set_globvar(int i) {
    globvar = i;
    return 0;
}

int callee(int a, int b) {
    return a + b;
}

int target(int param) {
    int x = param;
    
    
    set_globvar(x);
    int y = x;  
    x = 10;     
    
    return callee(x, y);  
}

int main(void) {
    if (target(4) != 14) {
        return 1;
    }
    if (globvar != 4) {  
        return 2;
    }
    return 0;  
}