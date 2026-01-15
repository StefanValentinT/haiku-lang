/* Test that we can eliminate dead code inside of a larger, non-dead
 * control structure
 * */

int callee(void) {
    return 1 / 0;
}

int target(void) {
    int result = 105;
    
    for (int i = 0; i < 100; i = i + 1) {
        if (0) {  
                  
            return callee();
        }
        result = result - i;
    }
    return result;
}

int main(void) {
    if (target() != -4845) {
        return 1; 
    }
    return 0; 
}