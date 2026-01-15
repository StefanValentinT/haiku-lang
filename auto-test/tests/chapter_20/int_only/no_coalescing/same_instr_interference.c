/* Test that addl x, y and similar make x and y interfere if x is live
 * afterward. Just test for correctness, don't inspect assembly.
 * Only guaranteed to work as intended after implementing register coalescing.
 */


int main(void) {
    
    int a = id(1);
    /* movl    %a, %b # if we don't recognize that a and b interfere,
     *                # we'll coalesce them
     * addl    %a, %b # creates interference b/c a is still live after
     */
    int b = a + a;

    
    
    
    
    check_one_int(-1, -1);

    
    check_one_int(a, 1);
    check_one_int(b, 2);

    
    int c = id(3);
    /* movl    $c, %d # if we don't recognize that a and b interfere ,
     *                # we'll coalesce them
     * subl    $c, %d # creates interference b/c a is still live after
     */
    int d = c - c;
    
    
    
    
    check_one_int(0, 0);

    
    check_one_int(c, 3);
    check_one_int(d, 0);

    
    int x = id(4);
    /* movl    %x, %y # if we don't recognzie that x and y interfere ,
     *                # we'll coalesce them
     * imul    %x, %y # creates interference b/c x is still live after
     */
    int y = x * x;
    
    
    
    
    check_one_int(-1, -1);

    
    check_one_int(x, 4);
    check_one_int(y, 16);
    return 0;
}
