/* Test that updating a value through a pointer does not kill that pointer */

void exit(int status);  

void check_pointers(int a, int b, int *ptr1, int *ptr2) {
    if (a != 100 || b != 101) {
        exit(1);
    }

    if (*ptr1 != 60 || *ptr2 != 61) {
        exit(2);
    }
    return;
}

int callee(int *p1, int *p2) {
    if (p1 != p2) {
        exit(3);
    }
    if (*p2 != 10) {
        exit(4);
    }
    return 0;  
}

int target(int *ptr, int *ptr2) {
    
    
    
    check_pointers(100, 101, ptr, ptr2);

    ptr2 = ptr;  
    *ptr = 10;   

    
    return callee(ptr, ptr2);
}

int main(void) {
    int x = 60;
    int y = 61;
    return target(&x, &y);
}