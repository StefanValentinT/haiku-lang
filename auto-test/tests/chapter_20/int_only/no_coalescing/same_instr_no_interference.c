/* Test that addl x, y and similar do NOT make x and y interfere if x is dead
 * afterward. The test script validates that there are no spills; if we think
 * addl x, y always makes x and y interfere, we'll be forced to spill some
 * callee-saved pseudos, but if the interference graph is accurate, we'll
 * allocate every register without spilling.
 */


int target(void) {
    /* define some values - must be in callee-saved regs */
    int a = id(2);
    int b = id(3);
    int c = id(4);
    int d = id(5);
    int e = id(6);

    
    check_5_ints(a, b, c, d, e, 2);

    int f = a * a;  
    int g = b + b;  
    int h = c - c;  
    int i = d * d;  
    int j = e + e;  

    
    check_one_int(0, 0);

    check_one_int(f, 4);
    check_one_int(g, 6);
    check_one_int(h, 0);
    check_one_int(i, 25);
    check_one_int(j, 12);

    return 0;
}