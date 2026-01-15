/* Test that we recognize aliased non-static variables are live
 * just after function calls but dead at function exit
 * */

int b = 0;

void callee(int *ptr) {
    b = *ptr;
    *ptr = 100;
}

int target(void) {
    int x = 10;
    callee(&x);  
    int y = x;
    x = 50;  
    return y;
}

int main(void) {
    int a = target();
    if (a != 100) {
        return 1; 
    }
    if (b != 10) {
        return 2; 
    }
    return 0; 
}