/* Test that we correctly track both implicit type conversions via array decay
 * and explicit casts
 */


int main(void) {
    long arr[4] = {-1,-2,-3,-4};

    
    if (arr != (long *) arr) {
        return 1;
    }

    
    
    if ((long (*)[4]) arr != &arr) {
        return 2;
    }

    
    
    
    
    unsigned long *unsigned_arr = (unsigned long *)arr;
    if (unsigned_arr[0] != 18446744073709551615UL) {
        return 3;
    }

    if (unsigned_arr[3] != 18446744073709551612UL) {
        return 4;
    }

    return 0;
}