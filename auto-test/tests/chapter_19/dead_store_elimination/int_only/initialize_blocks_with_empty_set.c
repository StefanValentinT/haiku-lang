/* Test that we initialize each block in the CFG with an empty set of
 * live variables. Specifically, this test will fail if each block is
 * initialized with the set of all static variables.
 */


int j = 3;
int target(void) {
    static int i;
    i = 10;  
             
             
             
    while (j > 0) {
        j = j - 1;
    }
    i = 0;
    return 0;
}

int main(void) {
    target();
    return (j == 0);  
}