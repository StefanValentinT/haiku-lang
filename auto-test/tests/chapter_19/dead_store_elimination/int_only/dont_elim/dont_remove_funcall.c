/* Test that we never optimize away function calls,
 * even if they're dead stores (i.e. update dead variables)
 * because they can have side effects */

int putchar(int c);

int main(void) {
    
    
    
    
    int x = putchar(67);
    return 0;
}