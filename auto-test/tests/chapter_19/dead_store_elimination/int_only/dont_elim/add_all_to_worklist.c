/* Make sure we add every basic block to the worklist
 * at the start of the iterative algorithm
 */
int putchar(int c);

int f(int arg) {
    int x = 76;
    if (arg < 10) {
        
        
        x = 77;
    }
    
    
    if (arg)
        putchar(x);
    return 0;
}

int main(void) {
    f(0);
    f(1);
    f(11);
    return 0;
}