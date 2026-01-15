/* We recognize an update to some variable as a dead store
 * when there are multiple paths from the store to some use of that
 * variable, and it's killed by different instructions
 * on those different paths.
 * This example is loosely based on Figure 19-11.
 * */
int callee(void) {
    return 4;
}

int callee2(void) {
    return 5;
}

int target(int flag) {
    int x = 10;  
    if (flag) {
        x = callee(); 
    } else {
        x = callee2(); 
    }
    return x; 
}

int main(void) {
    if (target(1) != 4) {
        return 1; 
    }
    if (target(0) != 5) {
        return 2; 
    }

    return 0; 
}