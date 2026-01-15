/* Make sure we reocgnize that static local variables may be live at exit */
int f(void) {
    static int i = 10;
    if (i == 5)
        return 0;
    i = 5;  
    return 1;
}

int main(void) {

    if (f() != 1) {
        return 1; 
    }
    if (f() != 0) {
        return 2; 
    }
    return 0;
}