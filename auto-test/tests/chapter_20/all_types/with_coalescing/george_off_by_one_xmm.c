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


double glob = 0.0;

int target(double a) {

    
    
    
    
    
    
    
    
    
    

    double one = 2.0 - a;
    double two = one + one;
    double three = 2.0 + one;
    double four = two * two;
    double five = 6.0 - one;
    double six = two * three;
    double seven = one + 6.0;
    double eight = two * 4.0;
    double nine = three * three;
    double ten = four + six;
    double eleven = 16.0 - five;
    double twelve = eleven + one;
    double thirteen = five + eight;
    double fourteen = seven * two;

    
    glob = one;

    
    check_14_doubles(1, two, three, four, five, six, seven, eight, nine, ten,
                     eleven, twelve, thirteen, fourteen, 1);

    
    check_one_double(glob, 1.0);
    return 0;
}