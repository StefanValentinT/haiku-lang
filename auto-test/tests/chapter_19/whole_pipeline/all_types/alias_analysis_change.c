/* Test that we rerun alias analysis with each pipeline iteration */

int putchar(int c);

int foo(int *ptr) {
    putchar(*ptr);
    return 0;
}

int target(void) {
    int x = 10;  
    int y = 65;
    int *ptr = &y;
    if (0) {
        
        
        
        ptr = &x;
    }
    x = 5;     
               
    foo(ptr);  
               

    return 0;
}

int main(void) {
    return target();
}