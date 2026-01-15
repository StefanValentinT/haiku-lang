/* Test case based on Figure 19-8:
 * Make sure we run iterative algorithm until the results converge.
 * */
static int called_counter = 0;

int callee(int i) {
    if (i == 3 && called_counter == 0) {
        
        called_counter = 1;
        return 1;
    }
    if (i == 4 && called_counter == 1) {
        
        called_counter = 2;
        return 0;
    }

    
    
    called_counter = -1;
    return 0;
}

int target(void) {
    int y = 3;
    int keep_looping;
    do {
        
        
        
        
        keep_looping = callee(y);
        y = 4;
    } while (keep_looping);  
    return y;                
}

int main(void) {
    int result = target();
    if (result != 4) {
        return 1;
    }
    if (called_counter != 2) {
        return 2;
    }
    return 0;  
}