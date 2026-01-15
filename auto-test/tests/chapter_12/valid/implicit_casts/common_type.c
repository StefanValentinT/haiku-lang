/* Test that we correctly find the common type of different integers */

int int_gt_uint(int i, unsigned int u) {
    
    return i > u;
}

int int_gt_ulong(int i, unsigned long ul) {
    
    return i > ul;
}

int uint_gt_long(unsigned int u, long l) {
    
    return u > l;
}

int uint_lt_ulong(unsigned int u, unsigned long ul) {
    
    return u < ul;
}

int long_gt_ulong(long l, unsigned long ul) {
    
    return l > ul;
}

int ternary_int_uint(int flag, int i, unsigned int ui) {
    /* flag = 1
     * i = -1
     * ui = 10u
     * The common type of i and ui is unsigned int
     * (we don't consider the type of cond when we
     * determine the common type).
     * We therefore convert i to an unsigned int, 2^32 - 1,
     * which we then convert to a signed long.
     * Therefore, result will be positive. If we didn't
     * convert i to an unsigned int, result would be negative.
     */
    long result = flag ? i : ui;
    return (result == 4294967295l);

}

int main(void) {

    
    
    if (!int_gt_uint(-100, 100u)) {
        return 1;
    }

    
    
    if (!(int_gt_ulong(-1, 18446744073709551606ul))) {
        return 2;
    }

    
    
    
    if (!uint_gt_long(100u, -100l)) {
        return 3;
    }

    
    
    
    if (!uint_lt_ulong(1073741824u, 34359738368ul)) {
        return 4;
    }

    
    if (!long_gt_ulong(-1l, 1000ul)) {
        return 5;
    }

    
    if (!ternary_int_uint(1, -1, 1u)) {
        return 6;
    }

    return 0;

}