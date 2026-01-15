/* Test constant folding of all operations on doubles and make sure they're
 * correctly rounded.
 * */


double target_add(void) {
    
    return 1.2345e60 + 1.;
}

double target_sub(void) {
    
    
    return 5.85543871245623688067e-311 - 5.85543871245574281503e-311;
}

double target_mult(void) {
    return 2.1 * 3.0;
}

double target_div(void) {
    return 1100.5 / 5000.;
}

double target_div_underflow(void) {
    
    return 0.5e-100 / 2e307;
}

double target_neg(void) {
    return -.000000275;
}

int target_not(void) {
    return !1e30;
}

int target_eq(void) {
    
    
    return 0.1 == 0.10000000000000001;
}

int target_neq(void) {
    
    
    return 5e-324 != 0.0;
}

int target_gt(void) {
    return 1e308 > 1e307;
}

int target_ge(void) {
    return 3.1 >= 3.1;
}

int target_lt(void) {
    
    
    return 0.1 < 0.10000000000000001;
}

int target_le(void) {
    return 0.5 <= 0.;
}

double target_negate_zero(void) {
    
    return -0.0;
}

double target_infinity(void) {
    
    return 1e308 * 2.;
}

int target_compare_infininty(void) {
    
    return 10e308 == 12e308;
}

int main(void) {
    
    if (target_add() != 1.2345e60) {
        return 1;
    }
    if (target_sub() != 5e-324) {
        return 2;
    }
    if (target_mult() != 6.300000000000001) {
        return 3;
    }

    if (target_div() != 0.2201) {
        return 4;
    }
    if (target_div_underflow() != 0.0) {
        return 5;
    }
    
    
    if (target_neg() + .000000275 != 0.0) {
        return 6;
    }

    
    if (target_not() != 0) {
        return 7;
    }
    if (!target_eq()) {
        return 8;
    }
    if (!target_neq()) {
        return 9;
    }
    if (!target_gt()) {
        return 10;
    }
    if (!target_ge()) {
        return 11;
    }
    if (target_lt()) {
        return 12;
    }
    if (target_le()) {
        return 13;
    }

    
    if (target_infinity() != 10e308) {
        return 14;
    }
    if (!target_compare_infininty()) {
        return 15;
    }

    
    
    if (!((1 / target_negate_zero()) < 0.0)) {
        return 16;
    }

    return 0;
}
