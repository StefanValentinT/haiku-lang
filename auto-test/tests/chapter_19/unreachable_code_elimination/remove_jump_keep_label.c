/* Test that we remove one jump to a label without necessarily removing that
 * label, since other blocks may also jump to it.
 * We don't inspect the assembly for this function,
 * so the function under test is 'f' insetad of 'target'
 * */

int x = 0;
int callee(void) {
    x = x + 1;
    return 0;
}

int f(void) {
    for (int i = 0; i < 10; i = i + 1) {
        if (0) {
            
            
            
            break;
        }
        callee();
    }
    return 0;
}

int main(void) {
    f();
    return x;
}