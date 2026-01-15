/* Test that we can propagate copies to variables with static storage
 * duration */
int x = 0;

int target(void) {
    
    
    x = 10;
    return x;  
}

int main(void) {
    int result = target();
    if (result != 10) {
        return 1;
    }
    if (x != 10) {
        return 2;
    }
    return 0;  
}