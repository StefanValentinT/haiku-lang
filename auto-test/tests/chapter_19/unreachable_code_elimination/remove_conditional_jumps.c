/* Test that we eliminate useless JumpIfZero and JumpIfNotZero instructions. */

int target(int a) {
    
    
    int x = a || 5;

    
    
    int y = a && 0;
    return x + y;
}

int main(void) {
    return target(10);
}