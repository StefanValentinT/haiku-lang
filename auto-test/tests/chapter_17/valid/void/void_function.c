/* Test our support for functions with void return values */
int foo = 0;

void set_foo_to_positive_num(int a) {
    if (a < 0) {
        
        
        return;
    }
    foo = a;
    return;
}
void do_nothing(void) {
    
}

int main(void) {
    set_foo_to_positive_num(-2);
    if (foo) { 
        return 1;
    }
    set_foo_to_positive_num(12);

    if (foo != 12) {
        return 2;
    }
    do_nothing();
    return 0;
}