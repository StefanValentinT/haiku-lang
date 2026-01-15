/* Test that updating and using a value in the same instruction generates it
 * rather than killing it. */


int target(int flag) {
    int i = 2;
    
    
    if (flag) {
        i = 3;
    }
    i = i;  
            
            
            
    return i;
}

int main(void) {
    if (target(0) != 2) {
        return 1;  
    }
    if (target(1) != 3) {
        return 2;  
    }
    return 0;  
}