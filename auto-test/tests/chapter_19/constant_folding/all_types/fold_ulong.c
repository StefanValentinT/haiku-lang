/* Test constant folding of all operations on unsigned longs;
 * make sure that they wrap around correctly,
 * that we evaluate them with unsigned division/comparison functions,
 * and that we can evaluate expressions requiring all 64 bits.
 */
unsigned long target_add(void) {
    
    return 18446744073709551615UL + 10ul;
}

unsigned long target_sub(void) {
    
    return 10ul - 12ul;
}

unsigned long target_mult(void) {
    
    return 9223372036854775808ul * 3ul;
}

unsigned long target_div(void) {
    return 18446744073709551614ul / 10ul;
}

unsigned long target_rem(void) {
    return 18446744073709551614ul % 10ul;
}

unsigned long target_complement(void) {
    return ~1ul;
}

unsigned long target_neg(void) {
    return -(9223372036854775900ul);
}

int target_not(void) {
    return !4294967296UL;  
}

int target_eq(void) {
    return 18446744073709551615UL == 18446744073709551615UL;
}

int target_neq(void) {
    
    
    return 9223372036854775809ul != 1ul;
}

int target_gt(void) {
    
    
    
    return 9223372036854775809ul > 1000ul;
}

int target_ge(void) {
    
    return 9223372036854775809ul >= 200ul;
}

int target_lt(void) {
    
    
    return 9223372036854775809ul < 1000ul;
}

int target_le(void) {
    return 9223372036854775809ul <= 200ul;
}

int target_le2(void) {
    
    return 9223372036854775809ul <= 9223372036854775809ul;
}

int main(void) {
    
    if (target_add() != 9ul) {
        return 1;
    }
    if (target_sub() != 18446744073709551614ul) {
        return 2;
    }
    if (target_mult() != 9223372036854775808ul) {
        return 3;
    }
    if (target_div() != 1844674407370955161ul) {
        return 4;
    }
    if (target_rem() != 4ul) {
        return 5;
    }

    
    if (target_complement() != 18446744073709551614ul) {
        return 6;
    }

    if (target_neg() + 9223372036854775900ul != 0) {
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

    if (!target_le2()) {
        return 15;
    }

    return 0;
}
