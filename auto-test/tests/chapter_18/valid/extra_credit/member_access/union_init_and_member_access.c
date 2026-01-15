/* Basic test of union type declarations, initializers, and member access */


union u {
    double d;
    long l;
    unsigned long ul;
    char c;
};

int main(void) {
    
    union u x = {20}; 

    
    if (x.d != 20.0) {
        return 1; 
    }

    
    union u *ptr = &x;
    ptr->l = -1l;
    if (ptr->l != -1l) {
        return 2; 
    }

    
    if (ptr->ul != 18446744073709551615UL) {
        return 3; 
    }

    if (x.c != -1) {
        return 4; 
    }
    return 0;
}