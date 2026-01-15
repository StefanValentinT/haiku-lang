/* Test that getting the address of a variable does _not_ make that variable
 * live.
 * */

int target(void) {
    int x = 4;  
                
    int *ptr = &x;
    return ptr == 0;
}

int main(void) {
    return target();
}