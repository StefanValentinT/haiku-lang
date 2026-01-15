/* Propagate copies of whole unions */

union u {
    long l;
    int i;
};

int callee(union u a, union u b) {
    if (a.l != -100) {
        return 1; 
    }
    if (b.l != -100) {
        return 2; 
    }

    return 0; 
}

int target(void) {
    union u u1 = {0};
    union u u2 = {-100};
    u1 = u2; 

    
    
    
    
    return callee(u1, u2);
}

int main(void) {
    return target();
}