/* Test constant folding with negative zero.
 * We couldn't test this in the constant folding stage because it requires
 * copy propagation.
 * See https:
 * a quick reference on arithmetic operations with -0.0
 * */


double copysign(double x, double y);  


int is_positive_zero(double d) {
    if (d != 0.0) {
        
        return 0;
    }
    
    return (copysign(5., d) == 5.0);
}

int is_negative_zero(double d) {
    if (d != 0.0) {
        
        return 0;
    }
    
    return (copysign(5., d) == -5.);
}

/* Comparisons */


int target_negative_zero_eq(void) {
    return 0.0 == -0.0;  
}

int target_negative_zero_neq(void) {
    return 0.0 != -0.0;  
}

int target_negative_zero_lt(void) {
    return -0.0 < 0.0;  
}

int target_negative_zero_gt(void) {
    return -0.0 > 0.0;  
}

int target_negative_zero_ge(void) {
    return -0.0 >= 0.0;  
}

int target_negative_zero_le(void) {
    return -0.0 <= 0.0;  
}


int target_neg_zero_branch(void) {
    if (-0.0) {
        return 1;
    }
    return 0;
}

int target_not_neg_zero(void) {
    return !-0.0;  
}

int target_neg_zero_and(void) {
    return -0.0 && 1;
}

/* Addition */
double target_add_negative_zero_to_self(void) {
    return -0. + -0.;  
}

double target_add_positive_to_negative_zero(void) {
    
    return -0. + 0.;
}

double target_add_negative_to_positive_zero(void) {
    return 0. + -0.;  
}

double target_add_negative_nonzero_to_negative_zero(void) {
    
    return -5.0 + -0.;
}

double target_add_positive_nonzero_to_negative_zero(void) {
    
    return -0. + 10.;
}

/* Subtraction */
double target_subtract_neg_zero_from_self(void) {
    return -0. - -0.;  
}

double target_subtract_pos_zero_from_neg_zero(void) {
    return -0. - 0.;  
}

double target_subtract_neg_zero_from_pos_zero(void) {
    return 0. - -0.;  
}

double target_subtract_pos_nonzero_from_neg_zero(void) {
    return -0. - 10.;  
}

/* Multiplication */
double target_negative_zero_mult(void) {
    return -0.0 * 15.4e10;  
}

double target_negative_zero_mult_negative(void) {
    return -100. * -0.;  
}

double target_negative_zero_squared(void) {
    return -0. * -0.;  
}

double target_neg_zero_mult_zero(void) {
    return 0. * -0.;  
}

double target_mult_underflow(void) {
    return -5.85543871245623688067e-320 *
           0.5e-5;  
}

/* division */

double target_div_neg_zero_by_pos_nonzero(void) {
    return -0. / 10.;  
}

double target_div_pos_zero_by_neg_nonzero(void) {
    return 0. / -10.;  
}

double target_div_neg_zero_by_neg_nonzero(void) {
    return -0. / -5.;  
}

double target_div_negative_underflow(void) {
    
    return 0.5e-100 / -2e307;
}

double target_div_pos_non_zero_by_neg_zero(void) {
    return 10. / -0.0;  
}

double target_div_neg_nonzero_by_zero(void) {
    return -10. / 0.;  
}

double target_div_neg_nonzero_by_neg_zero(void) {
    return -100. / -0.;  
}

/* negation */
double target_negate_neg_zero(void) {
    return -(-0.0);  
}



double target_negate_calculated_zero(void) {
    return -(50. - 50.);
}

int main(void) {
    if (target_negative_zero_eq() != 1) {
        return 1;  
    }
    if (target_negative_zero_neq() != 0) {
        return 2;  
    }
    if (target_negative_zero_lt() != 0) {
        return 3;  
    }
    if (target_negative_zero_gt() != 0) {
        return 4;  
    }
    if (target_negative_zero_ge() != 1) {
        return 5;  
    }
    if (target_negative_zero_le() != 1) {
        return 6;  
    }
    if (target_neg_zero_branch()) {
        return 7;  
    }
    if (target_not_neg_zero() != 1) {
        return 8;  
    }
    if (target_neg_zero_and() != 0) {
        return 9;  
    }

    double d;
    d = target_add_negative_zero_to_self();
    if (!is_negative_zero(d)) {
        return 10;  
    }
    d = target_add_positive_to_negative_zero();
    if (!is_positive_zero(d)) {
        return 11;  
    }
    d = target_add_negative_to_positive_zero();
    if (!is_positive_zero(d)) {
        return 12;  
    }
    d = target_add_negative_nonzero_to_negative_zero();
    if (d != -5.) {
        return 13;  
    }
    d = target_add_positive_nonzero_to_negative_zero();
    if (d != 10.) {
        return 14;  
    }

    d = target_subtract_neg_zero_from_self();
    if (!is_positive_zero(d)) {
        return 15;  
    }
    d = target_subtract_pos_zero_from_neg_zero();
    if (!is_negative_zero(d)) {
        return 16;  
    }
    d = target_subtract_neg_zero_from_pos_zero();
    if (!is_positive_zero(d)) {
        return 17;  
    }
    d = target_subtract_pos_nonzero_from_neg_zero();
    if (d != -10.) {
        return 18;  
    }

    d = target_negative_zero_mult();
    if (!is_negative_zero(d)) {
        return 19;  
    }
    d = target_negative_zero_mult_negative();
    if (!is_positive_zero(d)) {
        return 20;  
    }
    d = target_negative_zero_squared();
    if (!is_positive_zero(d)) {
        return 21;  
    }
    d = target_neg_zero_mult_zero();
    if (!is_negative_zero(d)) {
        return 22;  
    }
    d = target_mult_underflow();
    if (!is_negative_zero(d)) {
        return 23;  
    }

    d = target_div_neg_zero_by_pos_nonzero();
    if (!is_negative_zero(d)) {
        return 24;  
    }
    d = target_div_pos_zero_by_neg_nonzero();
    if (!is_negative_zero(d)) {
        return 25;  
    }
    d = target_div_neg_zero_by_neg_nonzero();
    if (!is_positive_zero(d)) {
        return 26;  
    }
    d = target_div_pos_non_zero_by_neg_zero();
    if (d >= -1.79e308) {  
        return 27;         
    }
    d = target_div_neg_nonzero_by_zero();
    if (d >= -1.79e308) {  
        return 28;         
    }
    d = target_div_neg_nonzero_by_neg_zero();
    if (d <= 1.79e308) {  
        return 29;        
    }
    d = target_div_negative_underflow();
    if (!is_negative_zero(d)) {
        return 30;
    }
    d = target_negate_neg_zero();
    if (!is_positive_zero(d)) {
        return 31;  
    }
    d = target_negate_calculated_zero();
    if (!is_negative_zero(d)) {
        return 32;  
    }
    return 0;  
}