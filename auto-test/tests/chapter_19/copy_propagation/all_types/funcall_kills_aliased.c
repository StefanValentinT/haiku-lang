/* Test that function calls kill all aliased variables, but not non-aliased
 * variables */

double *globl_ptr = 0;

void save_ptr(double *to_save) {
    globl_ptr = to_save;
}

void update_ptr(void) {
    *globl_ptr = 4.0;
}


int target(void) {
    int x = 10;    
    update_ptr();  

    return x;  
}


int kill_aliased(void) {
    double d = 1.0;
    double *ptr = &d;
    save_ptr(ptr);

    if (*globl_ptr != 1.0) {
        return 0;  
    }

    d = 2.0;  

    if (*globl_ptr != 2.0) {
        return 0;  
    }

    update_ptr();  
    return d;      
}

int main(void) {
    double d = 0.0;
    globl_ptr = &d;

    
    if (target() != 10) {
        return 1;  
    }

    
    if (d != 4.0) {
        return 2;  
    }

    
    d = 0.0;

    
    if (kill_aliased() != 4.0) {
        return 3;  
    }

    
    
    if (d != 0.0) {
        return 4;  
    }

    return 0;  
}
