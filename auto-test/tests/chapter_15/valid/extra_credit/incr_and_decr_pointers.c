
int main(void) {
    double x[3] = {0.0, 1.0, 2.0};
    double *ptr = x;
    
    if (++ptr != x + 1) {
        return 1;  
    }
    if (*ptr != 1.0) {
        return 2;  
    }

    
    if (ptr++ != x + 1) {
        return 3;  
    }
    if (ptr != x + 2) {
        return 4;
    }
    if (*ptr != 2.0) {
        return 5;  
    }

    
    if (--ptr != x + 1) {
        return 6;  
    }
    if (*ptr != 1.0) {
        return 7;  
    }

    
    if (ptr-- != x + 1) {
        return 8;  
    }
    if (*ptr != 0.0) {
        return 9;  
    }
    if (ptr != x) {
        return 10;  
    }

    return 0;  
}