/* Test that store instruction kills any copy
 * whose source or destination is aliased
 */


int aliased_src(int flag, int x, int *ptr) {
    int y = x;  
    if (flag) {
        ptr = &x;  
    }
    *ptr = 100;  

    return y;  
}


int aliased_dst(int flag, int x, int *ptr) {
    int y = x;  
    if (flag) {
        ptr = &y;  
    }
    *ptr = 100;  
    return y;    
}

int main(void) {
    int i = 0;
    
    
    if (aliased_src(0, 1, &i) != 1) {
        return 1;  
    }
    if (i != 100) {
        return 2;  
    }

    
    i = 0;
    if (aliased_src(1, 2, &i) != 2) {
        return 3;  
    }
    if (i != 0) {
        return 4;  
    }

    
    
    if (aliased_dst(0, 5, &i) != 5) {
        return 5;  
    }

    if (i != 100) {
        return 6;  
    }
    
    
    i = 0;
    if (aliased_dst(1, 5, &i) != 100) {
        return 7;  
    }

    if (i != 0) {
        return 8;  
    }

    return 0;  
}