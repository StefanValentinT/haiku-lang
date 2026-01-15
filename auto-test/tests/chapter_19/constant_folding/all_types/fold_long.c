/* Test constant folding of operations on long ints.
 * Make sure we correctly handle operations that require all 64 bits.
 * Tests do not involve any overflow, since that's undefined behavior.
 */
long target_add(void) {
    
    return 2147483647l + 1000l;
}

long target_sub(void) {
    
    return 1000l - 9223372036854773807l;
}

long target_mult(void) {
    
    return 35184372088832l * 4l;
}

long target_div(void) {
    
    return 9223372036854775807l / 3147483647l;
}

long target_rem(void) {
    
    return 9223372036854775807l % 3147483647l;
}

long target_complement(void) {
    
    return ~6148914691236517206l;
}

long target_neg(void) {
    
    
    return -(9223372036854775716l);
}

int target_not(void) {
    
    
    return !72110370596061184l;
}

int target_eq(void) {
    return 9223372036854775716l == 9223372036854775716l;
}

int target_neq(void) {
    
    return 72110370596061184l != 0l;
}

int target_gt(void) {
    
    
    return 549755813889l > 17592186044416l ;  
}

int target_ge(void) {
    return 400l >= 399l;
}

int target_lt(void) {
    
    return 17592186044416l < 549755813888l;  
}

int target_le(void) {
    
    return 2147483648l <= 0l;
}

long sub_result = 9223372036854772807l;
long complement_result = 6148914691236517207l;
long neg_result = 9223372036854775716l;

int main(void) {
    
    if (target_add() != 2147484647l) {
        return 1;
    }
    if (target_sub() != -sub_result) {
        return 2;
    }
    if (target_mult() != 140737488355328l) {
        return 3;
    }
    if (target_div() != 2930395538l) {
        return 4;
    }
    if (target_rem() != 1758008721l) {
        return 5;
    }

    
    if (target_complement() != -complement_result) {
        return 6;
    }

    if (target_neg() != -neg_result) {
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
    if (target_gt()) {
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
