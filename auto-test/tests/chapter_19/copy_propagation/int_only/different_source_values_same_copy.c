/* We can propagate x = y if it appears on all paths to some use of x,
 * even if y doesn't have the same value on all those paths.
 * Based on Figure 19-5.
 * */

int callee(int a, int b) {
    return a + b;
}
int target(int flag) {
    
    
    
    
    static int x;
    static int y;
    if (flag) {
        y = 20;
        x = y;
    } else {
        y = 100;
        x = y;
    }
    
    return callee(x, y);
}

int main(void) {
    int result = target(0);

    if (result != 200)
        return 1;

    result = target(1);
    if (result != 40)
        return 2;

    return 0;  
}