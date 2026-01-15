/* Check for off-by-one errors in the George test. Make sure we don't coalesce
 * pseudo p into hardreg h if p has a neighbor whose degree is exactly k.
 * The test script validates that there are no spills - we shouldn't need to
 * spill any pseudos, but we'll be forced to spill if we coalesce a pseudo
 * into a hard register when we shouldn't.
 * NOTE: we don't have an equivalent off-by-one test for Briggs b/c it's
 * adequately covered by other tests.
 *
 * This test was generated from
 * templates/chapter_20_templates/george_off_by_one.c.jinja.
 * */


int glob = 0;

int target(int a) {

    
    
    
    
    
    
    
    
    
    

    int one = 2 - a;
    int two = one + one;
    int three = 2 + one;
    int four = two * two;
    int five = 6 - one;
    int six = two * three;
    int seven = one + 6;
    int eight = two * 4;
    int nine = three * three;
    int ten = four + six;
    int eleven = 16 - five;
    int twelve = eleven + one;

    
    glob = one;

    
    check_12_ints(1, two, three, four, five, six, seven, eight, nine, ten,
                  eleven, twelve, 1);

    
    check_one_int(glob, 1);
    return 0;
}