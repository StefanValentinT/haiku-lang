/* Test that we recognize call to 'callee' is unreachable;
 * */

int callee(void) {
    return 100;
}

int target(int a) {
    if (a) {
        return 1;
    } else {
        return 2;
    }

    return callee();  
}
int main(void) {
    if (target(1) != 1) {
        return 1; 
    }
    if (target(0) != 2) {
        return 2; 
    }
    return 0; 
}