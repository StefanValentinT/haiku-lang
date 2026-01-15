

int main(void) {
    
    double d = 5.0;
    double *d_ptr = &d;
    
    *d_ptr *= 1000u;
    if (d != 5000.0) {
        return 1; 
    }
    int i = -50;
    int *i_ptr = &i;
    
    *i_ptr %= 4294967200U;
    if (*i_ptr != 46) {
        return 2; 
    }

    
    unsigned int ui = 4294967295U; 
    ui /= *d_ptr;
    
    if (ui != 858993u) {
        return 3; 
    }

    
    i = -10;
    unsigned long ul = 9223372036854775807ul; 
    unsigned long *ul_ptr = &ul;
    
    
    *i_ptr -= *ul_ptr;
    if (i != -9) {
        return 4; 
    }

    
    if (ul != 9223372036854775807ul) {
        return 5; 
    }

    return 0;
}