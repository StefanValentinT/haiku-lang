/* In most of our test cases, the dead store we remove is a Copy.
 * This test case validates that we can remove dead
 * Binary and Unary instructions too.
 * */


int a = 1;
int b = 2;

int target(void) {
    
    int unused = a * -b;
    return 5;
}

int main(void) {
    return target();
}