/* Test that we recognize that idiv updates EAX.
 * We won't examine the assembly output for this test case, we'll just make sure
 * it behaves correctly.
 * NOTE: this is only guaranteed to work as intended after we implement register
 * coalescing.
 *
 * This test program is generated from templates/chapter_20_templates/division_interference.c.jinja
 */


int glob = 3;

int target(void) {
    int dividend = glob * 16;

    
    

    /* mov    %dividend, %eax
     * cdq
     * idiv   $4 # update EAX, making it conflict with dividend,
     *           # which is still live
     */
    int quotient = dividend / 4;

    
    
    
    glob = dividend;

    
    check_one_int(quotient, 12);

    return 0;
}

int main(void) {
    target();
    check_one_int(glob, 48);
    return 0;
}