/* Test copy prop/constant folding of compound assignment with non-integer
 * types and type conversions
 */

 
 
int target_chars(void) {
    char c = 100;
    char c2 = 100;
    c += c2; 
    if (c != -56) {
        return 1; 
    }

    unsigned char uc = 200;
    c2 = -100;
    uc /= c2; 
    if (uc != 254) {
        return 2; 
    }

    uc -= 250.0; 
    if (uc != 4) {
        return 3;  
    }

    signed char sc = -70;
    sc *= c;
    if (sc != 80) {
        return 4; 
    }

    if ((sc %= c) != 24) {
        return 5; 
    }

    return 0; 
}



int target_double(void) {
    double d = 10.0;
    d /= 4.0;
    if (d != 2.5) {
        return 1;
    }
    d *= 10000.0;
    if (d != 25000.0) {
        return 2;
    }

    return 0;
}


int target_double_cast(void) {
    double d = 1000.5;
    /* When we perform compound assignment, we convert both operands
     * to their common type, operate on them, and convert the result to the
     * type of the left operand */
    d += 1000;
    if (d != 2000.5) {
        return 1;
    }

    unsigned long ul = 18446744073709551586ul;
    /* We'll promote e to the nearest double,
     * which is 18446744073709551616,
     * then subtract 1.5 * 10^19, which
     * results in 3446744073709551616.0,
     * then convert it back to an unsigned long
     */
    ul -= 1.5E19;
    if (ul != 3446744073709551616ul) {
        return 2;
    }
    /* We'll promote i to a double, add .99999,
     * then truncate it back to an int
     */
    int i = 10;
    i += 0.99999;
    if (i != 10) {
        return 3;
    }

    return 0;
}


int target_uint(void) {
    unsigned int x = -1u; 
    /* 1. convert x to a signed long, which preserves its value
     * 2. divide by -10, resulting in -429496729
     * 3. convert -429496729 to an unsigned int by adding 2^32
     */
    x /= -10l;

    if (x == 3865470567u) {
        return 0; 
    }

    return 1; 
}


int target_assign_long_to_int(void) {
    int i = -20;
    int b = 2147483647;
    int c = -5000000;

    /* This statement is evaluated as follows:
     * 1. sign-extend i to a long with value -20
     * 2. add this long to 2147483648, resulting in the long 2147483628,
     * 3. convert this to an int with value 2147483628 (this value
     * can be represented as an int)
     */
    i += 2147483648l;

    
    if (i != 2147483628) {
        return 1;
    }
    if (b != 2147483647) {
        return 2;
    }

    
    
    
    
    b /= -34359738367l;
    if (b) { 
        return 3;
    }

    
    if (i != 2147483628) {
        return 4;
    }
    if (c != -5000000) {
        return 5;
    }

    
    
    c *= 10000l;
    if (c != 1539607552) {
        return 6;
    }

    return 0;
}



int target_assign_to_long(void) {
    long l = -34359738368l; 
    int i = -10;
    /* We should convert i to a long, then subtract from l */
    l -= i;
    if (l != -34359738358l) {
        return 1;
    }
    return 0;
}

int main(void) {
    if (target_chars()) {
        return 1;
    }

    if (target_double()) {
        return 2;
    }

    if (target_double_cast()) {
        return 3;
    }

    if (target_uint()) {
        return 4;
    }

    if (target_assign_long_to_int()) {
        return 5;
    }

    if (target_assign_to_long()) {
        return 6;
    }

    return 0; 
}