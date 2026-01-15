/* Test that we correctly perform conversions "as if by assignment", including:
 * - actual assignment expressions
 * - initializers for automatic variables
 * - return statements
 * Implicit conversions of function arguments are in a separate test case, convert_function_arguments.c
 */


int return_truncated_long(long l) {
    return l;
}

long return_extended_int(int i) {
    return i;
}

int truncate_on_assignment(long l, int expected) {
    int result = l; 
    return result == expected;
}

int main(void) {

    

    /* return_truncated_long will truncate 2^32 + 2 to 2
     * assigning it to result converts this to a long
     * but preserves its value.
     */
    long result = return_truncated_long(4294967298l);
    if (result != 2l) {
        return 1;
    }

    /* return_extended_int sign-extends its argument, preserving its value */
    result = return_extended_int(-10);
    if (result != -10) {
        return 2;
    }

    

    /* This is 2^32 + 2,
     * it will be truncated to 2 by assignment
     */
    int i = 4294967298l;
    if (i != 2) {
        return 3;
    }

    

    
    if (!truncate_on_assignment(17179869184l, 0)) {
        return 4;
    }

    return 0;
}