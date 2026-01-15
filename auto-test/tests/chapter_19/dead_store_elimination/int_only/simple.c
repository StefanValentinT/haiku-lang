/* A basic test case for eliminating a dead store */


int target(void) {
    int x = 10; 
    return 3;
}

int main(void) {
    return target();
}