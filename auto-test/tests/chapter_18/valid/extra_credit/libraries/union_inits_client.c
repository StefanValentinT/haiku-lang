



int test_simple(void) {
    
    union simple x = { 123.45 };
    return validate_simple(&x);
}

int test_simple_converted(void) {
    
    
    
    union simple x = { 18446744073709550315UL };
    return validate_simple_converted(&x);
}


int test_nested(void) {
    
    union nested x = { {4294967395l, {{-1, -2, -3, -4, -5, -6, -7, -8, -9}}} };
    return validate_nested(&x);
}

int test_nested_partial_init(void) {
    
    union nested x = { {9000372036854775800l, {"string"}} };
    return validate_nested_partial(&x);
}

int main(void) {
    if (!test_simple()) {
        return 1;
    }

    if (!test_simple_converted()) {
        return 2;
    }

    if (!test_nested()) {
        return 3;
    }

    if (!test_nested_partial_init()) {
        return 4;
    }

    return 0;
}