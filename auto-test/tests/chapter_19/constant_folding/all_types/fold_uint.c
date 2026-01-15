/* Test constant folding of all operations on unsigned ints;
 * make sure they wrap around correctly
 * and that we evaluate them with unsigned division/comparison functions.
 */
unsigned int target_add(void) {
    
    return 4294967295U + 10u;
}

unsigned int target_sub(void) {
    
    return 10u - 12u;
}

unsigned int target_mult(void) {
    
    return 2147483648u * 3u;
}

unsigned int target_div(void) {
    
    return 4294967286u / 10u;
}

unsigned int target_rem(void) {
    
    return 4294967286u % 10u;
}

unsigned int target_complement(void) {
    return ~1u;
}

unsigned int target_neg(void) {
    return -10u;
}

int target_not(void) {
    return !65536u;  
}

int target_eq(void) {
    return 100u == 100u;
}

int target_neq(void) {
    
    
    return 2147483649u != 1u;
}

int target_gt(void) {
    
    
    
    return 2147483649u > 1000u;
}

int target_ge(void) {
    return 4000000000u >= 3999999999u;
}

int target_lt(void) {
    
    
    return 2147483649u < 1000u;
}

int target_le(void) {
    return 4000000000u <= 3999999999u;
}

int main(void) {
    
    if (target_add() != 9u) {
        return 1;
    }
    if (target_sub() != 4294967294U) {
        return 2;
    }
    if (target_mult() != 2147483648u) {
        return 3;
    }
    if (target_div() != 429496728u) {
        return 4;
    }
    if (target_rem() != 6u) {
        return 5;
    }

    
    if (target_complement() != 4294967294U) {
        return 6;
    }

    if (target_neg() + 10 != 0) {
        return 7;
    }

    if (target_not() != 0) {
        return 8;
    }

    
    if (!target_eq()) {
        return 9;
    }
    if (!target_neq()) {
        return 10;
    }
    if (!target_gt()) {
        return 11;
    }
    if (!target_ge()) {
        return 12;
    }
    if (target_lt()) {
        return 13;
    }
    if (target_le()) {
        return 14;
    }

    return 0;
}
