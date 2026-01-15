/* Test constant folding with negative numbers (including double and long);
 * we couldn't test this in the constant-folding stage because it requires
 * copy propagation.
 * */

/* long tests */

/* similar to int-only remainder_test but with long instead of int */
long target_remainder_test(void) {
    
    
    return -8589934585l % 4294967290l;
}

long target_long_subtraction(void) {
    
    
    return -4294967290l - 90l;
}

long target_long_division(void) {
    
    
    return (-4294967290l / 128l);
}

long target_long_complement(void) {
    return ~-9223372036854775807l;
}

/* double tests */
double target_double_add(void) {
    
    
    
    
    
    return -1.2345e60 + 1.;
}

double target_double_sub(void) {
    
    
    
    
    return -5.85543871245623688067e-311 - -5.85543871245574281503e-311;
}

double target_double_div(void) {
    
    
    
    return -1100.5 / 5000.;
}

int main(void) {
    
    if (target_remainder_test() != -5l) {
        return 1;  
    }
    if (target_long_subtraction() != -4294967380l) {
        return 2;  
    }
    if (target_long_division() != -33554431l) {
        return 3;  
    }
    if (target_long_complement() != 9223372036854775806l) {
        return 4;  
    }
    
    if (target_double_add() != -1.2345e60) {
        return 5;  
    }
    if (target_double_sub() != -5e-324) {
        return 6;  
    }
    if (target_double_div() != -0.2201) {
        return 7;  
    }
    return 0;
}