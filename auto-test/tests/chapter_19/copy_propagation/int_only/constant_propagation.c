/* A basic test of constant propagation in a function with no control flow
 * structures
 * */
int target(void) {
    int x = 3;
    int y = x;
    return x + y;  
}

int main(void) {
    return target();
}