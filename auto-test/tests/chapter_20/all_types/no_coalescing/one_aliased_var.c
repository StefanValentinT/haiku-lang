/* Make sure that one aliased pseudoregister doesn't prevent us from allocating
 * pseudos for other, non-aliased pseudoregisters.
 * We have to put arguments one and one_d on the stack because they're aliased,
 * but should be able to store all other pseudos in registers.
 */


void increment(int *ptr) {
    *ptr = *ptr + 1;
    return;
}

double deref(double *ptr) {
    return *ptr;
}





int target(int one, int two, int three, double one_d) {
    int *ptr = &one;
    double *d_ptr = &one_d;
    check_one_double(deref(d_ptr), 1.0);
    increment(ptr);  
    long five = two + three;
    check_one_int(one, 2);
    check_one_long(five, 5l);
    return 0;
}