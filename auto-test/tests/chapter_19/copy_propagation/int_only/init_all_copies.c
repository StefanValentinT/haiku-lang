/* Test that we initialize each basic block with the set of all copies
 * in the function
 * */

int counter = 0;

int increment_counter(void) {
    counter = counter + 1;
    return 0;
}

int target(void) {
    int y = 3;
    do {
        
        
        
        
        increment_counter();
    } while (counter < 5);
    return y;  
}

int main(void) {
    int result = target();
    if (result != 3) {
        return 1;
    }

    
    if (counter != 5) {
        return 2;
    }

    return 0;  
}