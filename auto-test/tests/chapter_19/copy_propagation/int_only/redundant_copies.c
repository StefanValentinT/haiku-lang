/* Test that we eliminate y = x and y = x if we can prove that x and y
 * already have the same values.
 * After copy propagation and cleanup unreachable code elimination,
 * target should contain no control-flow instructions
 * */

int target(int flag, int flag2, int y) {
    int x = y;

    if (flag) {
        y = x;  
                
    }
    if (flag2) {
        x = y;  
                
    }
    return x + y;
}

int main(void) {
    return target(0, 1, 10);  
}