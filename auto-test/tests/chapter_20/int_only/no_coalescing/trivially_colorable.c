/* A simple function that's easy to color without spilling.
 * The test script validates that we don't spill any pseudoregisters in target.
 */


int target(int one, int two) {
    
    
    int three = one + two;
    int four = two * two;
    int five = three + two;
    return check_5_ints(one, two, three, four, five, 1);
}
