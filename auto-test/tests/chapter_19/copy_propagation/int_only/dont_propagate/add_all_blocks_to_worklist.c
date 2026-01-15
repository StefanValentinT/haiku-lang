/* Test that we add every block to the worklist
 * at the start of the iterative algoirthm
 * */

int global;

int flag = 1;

int f(void) {
    global = 100;
    return 0;
}

int main(void) {
    
    
    global = 0;

    
    
    
    
    
    if (flag) {
        f();  
    }

    
    
    return global;
}
