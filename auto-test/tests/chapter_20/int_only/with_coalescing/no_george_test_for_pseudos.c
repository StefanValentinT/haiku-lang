/* Test that we don't apply the George test to pseudoregisters.
 * This program includes one pseudoregister that must spill, which is connected
 * by mov instructions to two other pseudoregisters. If we used the George test
 * to decide when to coalesce pseudos, we'd coalesce the pseudo that will spill
 * with one or both of these other pseudos, which would increase the number of
 * spill instructions in the program. We'll inspect the assembly for target to
 * make sure it has no more than the expected number of spill instructions.
 * */





int target(void) {
    
    
    
    
    
    
    int a = id(1);
    int b = id(2);

    
    int x = id(10);
    check_one_int(x, 10);

    
    int c = x;
    if (!a) {
        
        
        c = 100;
    }
    int d = id(3);
    int e = id(4);
    int f = id(5);

    
    
    check_5_ints(a, b, d, e, f, 1);
    check_5_ints(a + 3, b + 3, d + 3, e + 3, f + 3, 4);
    check_5_ints(a + 4, b + 4, d + 4, e + 4, f + 4, 5);
    check_one_int(a * 2, 2);
    check_one_int(b * 2, 4);
    check_one_int(d * 2, 6);
    check_one_int(e * 2, 8);
    check_one_int(f * 2, 10);
    check_one_int(a * 3, 3);
    check_one_int(b * 3, 6);
    check_one_int(d * 3, 9);
    check_one_int(e * 3, 12);
    check_one_int(f * 3, 15);

    
    
    int g = c;
    if (!f) {
        
        
        g = -1;
    }

    
    check_one_int(g, 10);

    return 0;
}