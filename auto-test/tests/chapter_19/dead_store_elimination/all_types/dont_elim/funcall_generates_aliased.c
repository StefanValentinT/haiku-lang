/* A function call generates every aliased variable,
 * even if that variable isn't passed as a function argument
 * */
static int *i;

void set_ptr(int *arg) {
    i = arg;
}

int get_ptr_val(void) {
    return *i;
}

int main(void) {
    int x = 1;
    set_ptr(&x);
    x = 4;  
    return get_ptr_val(); 
}