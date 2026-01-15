/* Test constant folding of casts from integer types to double
 * making sure the results are correctly rounded.
 * */


double target_from_int(void) {
    return (double)1000;
}



double target_from_uint(void) {
    return (double)4294967290u;
}





double target_from_long(void) {
    return (double)4611686018427388416l;
}




double target_from_ulong(void) {
    return (double)9223372036854776833ul;
}



double target_implicit(void) {
    return 1000;
}

int main(void) {
    if (target_from_int() != 1000.0) {
        return 1;
    }
    if (target_from_uint() != 4294967290.0) {
        return 2;
    }
    if (target_from_long() != 4611686018427387904.0) {
        return 3;
    }
    if (target_from_ulong() != 9223372036854777856.0) {
        return 4;

    }
    if (target_implicit() != 1000.0) {
        return 5;
    }
    return 0;
}