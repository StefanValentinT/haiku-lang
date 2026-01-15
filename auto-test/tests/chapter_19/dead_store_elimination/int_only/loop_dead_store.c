/* Test that we can detect dead stores in a function with a loop */
int putchar(int c);  

int target(void) {
    int x = 5;   
    int y = 65;  
    do {
        x = y + 2;  
        if (y > 70) {
            
            
            x = y + 3;
        }
        y = putchar(x) + 3;  
    } while (y < 90);
    if (x != 90) {
        return 1;  
    }
    if (y != 93) {
        return 2;  
    }
    return 0;  
}

int main(void) {
    return target();
}