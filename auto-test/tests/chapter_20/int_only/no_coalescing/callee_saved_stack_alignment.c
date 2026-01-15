/* Test that we adjust stack alignment to account for callee-saved registers.
 * The check_alignment function, which is written in assembly, validates that
 * RSP is aligned correctly and exits early if not.
 * The test script doesn't inspect assembly for this case, just checks the
 * exit code.
 * */




int check_alignment(int exit_code);


int test1(void) {
    int a = id(1);
    int b = id(2);
    int c = id(3);
    check_alignment(-1);
    check_one_int(a, 1);
    check_one_int(b, 2);
    check_one_int(c, 3);
    return 0;
}


int test2(void) {
    int a = id(4);
    int b = id(5);
    check_alignment(-2);
    check_one_int(a, 4);
    check_one_int(b, 5);
    return 0;
}


int test3(void) {

    
    
    int a = id(4);
    int b = id(5);
    int c = id(6);
    int d = id(7);
    int e = id(8);
    int f = id(9);
    int g = id(10);
    int h = id(11);
    check_alignment(-3);
    check_5_ints(a, b, c, d, e, 4);
    check_one_int(f, 9);
    check_one_int(g, 10);
    check_one_int(h, 11);
    return 0;
}