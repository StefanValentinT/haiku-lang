/* Make sure we use all hardregs rather than spill;
 * Create 12 pseudos that all interfere with each other
 * and make sure we assign all of them to hardregs
 * This test program is generated from templates/chapter_20_templates/use_all_hardregs.c.jinja
 * */

int global_one = 1;  

int target(void) {
    
    

    int one = 2 - global_one;
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
    int twelve = six + six;

    
    
    check_12_ints(one, two, three, four, five, six, seven, eight, nine, ten,
                  eleven, twelve, 1);
    return 0;  
}