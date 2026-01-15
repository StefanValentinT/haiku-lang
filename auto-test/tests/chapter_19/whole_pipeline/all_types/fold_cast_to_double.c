/* Constant-folding tests for conversions to double from chars and negative
 * ints; couldn't test these before because we need copy prop to fully evaluate
 * them.
 * */


double copysign(double x, double y);  

double target_from_neg_int(void) {
    return (double)-2147483647;  
}




double target_from_neg_long(void) {
    return (double)-4611686018427388416l;
}


double target_from_char(void) {
    char c = 127;
    return (double)c;
}


double target_from_schar(void) {
    char c = -127;
    return (double)c;
}


double target_from_uchar(void) {
    unsigned char u = 255;
    return (double)u;
}



double target_from_truncated_char(void) {
    char c = -129;
    return (double)c;  
}



double target_from_truncated_uchar(void) {
    unsigned char c = 1000;
    return (double)c;  
}

double target_from_negated_int_zero(void) {
    
    
    return -0;
}

int main(void) {
    if (target_from_neg_int() != -2147483647.) {
        return 1;
    }
    if (target_from_neg_long() != -4611686018427387904.0) {
        return 2;
    }
    if (target_from_char() != 127) {
        return 3;
    }
    if (target_from_schar() != -127) {
        return 4;
    }
    if (target_from_uchar() != 255) {
        return 5;
    }
    if (target_from_truncated_char() != 127) {
        return 6;
    }
    if (target_from_truncated_uchar() != 232) {
        return 7;
    }
    double zero = target_from_negated_int_zero();
    if (zero != 0 || copysign(5., zero) != 5.) {
        return 8;
    }
    return 0;  
}