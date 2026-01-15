/* Test constant folding with infinity.
 * We couldn't test this in the constant folding stage because it requires
 * copy propagation.
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

int target_infinity_equal(void) {
    
    
    
    return 1.0 / 0.0 == 11e330;
}

int target_infinity_gt(void) {
    
    
    return 1.0 / 0.0 > 1.79E308;
}

int target_neg_infinity_lt(void) {
    
    
    return -1.0 / 0.0 < -1.79E308;
}


double target_add_infinity(void) {
    return (1.0 / 0.0) + 1000e10;
}


double target_sub_infinity(void) {
    return (1.0 / 0.0) - 1000e10;
}



double target_mult_infinity(void) {
    return (1.0 / 0.0) * 25.;  
}

double target_mult_neg_infinity(void) {
    return (-1.0 / 0.0) * 25.;  
}

double target_mult_neg_infinity_by_neg_number(void) {
    return (-1.0 / 0.0) * -25.;  
}



double target_div_infinity_by_num(void) {
    return (1. / 0.) / 5.;
}


double target_negate_inf(void) {
    double infin = 1.0 / 0.0;
    return -infin;
}





double target_mult_overflow(void) {
    return 2e300 * 10e20;  
}

double target_div_overflow(void) {
    return 1e308 / -10e-20;  
}

double target_add_overflow(void) {
    return 1.79e308 + 1e308;  
}

double target_sub_overflow(void) {
    return -1e308 - 1e308;  
}



double target_zero_div_by_inf(void) {
    return 0. / (3.0 / 0.);  
}

double target_zero_div_by_neg_inf(void) {
    return 0. / (3.0 / -0.);  
}

double target_negative_zero_div_by_inf(void) {
    return -0. / (0.005 / 0.);  
}


int target_infinity_is_true(void) {
    double infin = 2345.0 / 0.0;
    if (infin) {
        return 1;  
    }
    return 0;  
}

double zero = 0.;

int main(void) {
    
    
    
    double infinity = 1. / zero;

    if (!target_infinity_equal()) {
        return 1;  
    }
    if (!target_infinity_gt()) {
        return 2;  
    }
    if (!target_neg_infinity_lt()) {
        return 3;  
    }

    if (target_add_infinity() != infinity) {
        return 4;  
    }

    if (target_sub_infinity() != infinity) {
        return 5;  
    }
    if (target_mult_infinity() != infinity) {
        return 6;  
    }

    if (target_mult_neg_infinity() != -infinity) {
        return 7;  
    }
    if (target_mult_neg_infinity_by_neg_number() != infinity) {
        return 8;  
    }
    if (target_div_infinity_by_num() != infinity) {
        return 9;  
    }
    if (target_negate_inf() != -infinity) {
        return 10;  
    }
    if (target_mult_overflow() != infinity) {
        return 11;  
    }
    if (target_div_overflow() != -infinity) {
        return 12;  
    }
    if (target_add_overflow() != infinity) {
        return 13;  
    }
    if (target_sub_overflow() != -infinity) {
        return 14;  
    }
    double d = target_zero_div_by_inf();
    if (!is_positive_zero(d)) {
        return 15;  
    }
    d = target_zero_div_by_neg_inf();
    if (!is_negative_zero(d)) {
        return 16;  
    }
    d = target_negative_zero_div_by_inf();
    if (!is_negative_zero(d)) {
        return 17;  
    }
    if (target_infinity_is_true() != 1) {
        return 18;  
    }
    return 0;  
}