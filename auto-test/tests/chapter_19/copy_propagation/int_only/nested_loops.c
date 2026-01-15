/* A test case that takes even longer than fig_19_8.c to converge;
 * some blocks need to be visited three times before the algorithm converges.
 * */

static int outer_flag = 0;
static int inner_flag = 1;


int inner_loop1(int a, int b, int c, int d, int e, int f) {
    
    
    if (a != 1 || b != 11 || c != 12 || d != 4 || e != 20 || f != 100) {
        return 0;  
    }
    return 1;  
}

int inner_loop2(int a, int b, int c, int d, int e, int f) {
    if (outer_flag == 0) {
        
        if (a != 1 || b != 2 || c != 3 || d != 4 || e != 5 || f != 100) {
            return 0;  
        }
    } else {
        
        if (a != 10 || b != 11 || c != 12 || d != 4 || e != 20 || f != 100) {
            return 0;  
        }
    }

    return 1;  
}

int inner_loop3(int a, int b, int c, int d, int e, int f) {
    if (outer_flag == 0) {
        if (inner_flag == 2) {
            
            if (a != 1 || b != 11 || c != 3 || d != 4 || e != 5 || f != 100) {
                return 0;  
            }
        } else {
            
            if (a != 1 || b != 11 || c != 12 || d != 4 || e != 5 || f != 100) {
                return 0;  
            }
        }
    } else {
        
        if (a != 10 || b != 11 || c != 12 || d != 4 || e != 20 || f != 100) {
            return 0;  
        }
    }

    return 1;  
}

int inner_loop4(int a, int b, int c, int d, int e, int f) {
    
    
    return a + b + c + d + e + f;
}

int validate(int a, int b, int c, int d, int e, int f) {
    
    if (a != 10 || b != 11 || c != 12 || d != 4 || e != 20 || f != 100) {
        return 0;  
    }
    return 1;  
}

int target(void) {
    
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int f = 100;

    
    while (outer_flag < 2) {
        
        while (inner_flag < 1) {
            if (!inner_loop1(a, b, c, d, e, f)) {
                return 1;  
            }
            a = 10;
            inner_flag = 1;
        }

        
        while (inner_flag < 2) {
            if (!inner_loop2(a, b, c, d, e, f)) {
                return 2;  
            }
            b = 11;
            
            
            inner_flag = 2;
        }

        
        while (inner_flag < 4) {
            if (!inner_loop3(a, b, c, d, e, f)) {
                return 3;  
            }
            
            inner_flag = inner_flag + 1;
            c = 12;
        }

        
        while (inner_flag < 4) {
            inner_loop4(a, b, c, d, e, f);
            d = 13;
        }

        e = 20;
        f = 100;
        outer_flag = outer_flag + 1;
        
        inner_flag = 0;
    }

    if (!validate(a, b, c, d, e, f)) {  
        return 4;
    }

    return 0;  
}

int main(void) {
    return target();
}