/* Test that we eliminate dead stores to static and global variables */

int i = 0;

int target(int arg) {
    i = 5;  
    i = arg;
    return i + 1;
}

int main(void) {
    int result1 = target(2);
    if (i != 2) {
        return 1;  
    }
    if (result1 != 3) {
        return 2;  
    }
    int result2 = target(-1);
    if (i != -1) {
        return 3;  
    }
    if (result2 != 0) {
        return 4;  
    }
    return 0;  
}