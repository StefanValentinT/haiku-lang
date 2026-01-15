/* Test that we can cast expressions to void */

int x;

int set_x(int i) {
    x = i;
    return 0;
}

void do_nothing(void) {
    ;
}

int main(void) {
    (void) x; 

    
    (void) set_x(12);

    
    (void) do_nothing();
    return x;
}