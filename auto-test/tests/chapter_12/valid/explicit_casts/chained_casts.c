/* The order in which multiple casts are applied matters */


unsigned int ui = 4294967200u; 

int main(void) {


    /* In this case we
     * 1. convert ui to a signed int by computing ui - 2^32, producing -96
     * 2. signed-extend the result, which preserves the value of -96
     * Note that if we cast ui directly to a signed long, its value wouldn't change
     */
    if ((long) (signed) ui != -96l)
        return 1;

    /* In this case we
     * 1. convert ui to a signed int by computing ui - 2^32, producing -96
     * 2. convert this signed int to an unsigned long by computing -96 + 2^64
     * Note that if we converted ui directly to an unsigned long, its value
     * wouldn't change
     */
    if ((unsigned long) (signed) ui != 18446744073709551520ul)
        return 2;

    return 0;
}