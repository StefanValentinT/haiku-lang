/* When converting uint to double, make sure we use MovZeroExtend rather than
 * mov to convert uint to long before converting to double, and that
 * we don't coalesce the MovZeroExtend instruction. Just validate
 * behavior, don't inspect assembly.
 * */


long one = 1l;

int main(void) {
    
    
    
    
    
    
    
    
    
    
    
    
    

    long neg1 = -one;
    unsigned int uint_max = (unsigned int)neg1;
    double d = (double)uint_max;
    check_one_double(d, 4294967295.0);
    return 0;
}
