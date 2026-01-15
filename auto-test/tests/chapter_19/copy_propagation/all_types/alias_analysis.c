/* Test that alias analysis allows us to propagate some copies
 * from variables whose address has been taken. */
int callee(int *ptr) {
    if (*ptr != 10) {
        return 0;  
    }
    *ptr = -1;
    return 1;
}

int target(int *ptr1, int *ptr2) {
    int i = 10;          
    int j = 20;          
    *ptr1 = callee(&i);  
                         
    *ptr2 = i;

    i = 4;  

    
    
    
    
    return i + j;
}

int main(void) {
    int callee_check1;
    int callee_check2;
    int result = target(&callee_check1, &callee_check2);
    if (callee_check1 != 1) {
        return 1;
    }
    if (callee_check2 != -1) {
        return 2;
    }
    if (result != 24) {
        return 3;
    }
    return 0;
}