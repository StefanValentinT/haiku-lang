/* Test constant folding of all conversions from longer to shorter integer
 * types. For now, we just verify that the behavior is correct, without
 * inspecting the assembly code; we can't tell whether a truncate operation was
 * constant folded because it turns into a single 'mov' instruction either way.
 * The whole_pipeline/ folder has more robust tests for constant folding of
 * truncate operations - in these tests, constant-folding truncate enables
 * other optimizations.
 */



int long_to_int(void) {
    
    return (int)35218731828434l;
}

unsigned int long_to_uint(void) {
    
    return (unsigned int)35218731828434l;
}

char long_to_char(void) {
    
    return (char)9223372036854775807l;
}

signed char long_to_schar(void) {
    
    return (signed char)4611686018427388032l;
}

unsigned char long_to_uchar(void) {
    
    return (unsigned char)4294967295UL;
}


int ulong_to_int(void) {
    
    return (int)18446744073709551615UL;
}

unsigned int ulong_to_uint(void) {
    return (unsigned int)18446744073709551615UL;
}

char ulong_to_char(void) {
    return (char)4294967295UL;
}

signed char ulong_to_schar(void) {
    return (signed char)4611686018427388032ul;
}

unsigned char ulong_to_uchar(void) {
    
    return (unsigned char)9223372036854776063ul;
}


char int_to_char(void) {
    return (char)1274;
}

signed char int_to_schar(void) {
    
    return (signed char)2147483647;
}

unsigned char int_to_uchar(void) {
    return (unsigned char)1274;
}


char uint_to_char(void) {
    return (char)2147483901u;  
}

signed char uint_to_schar(void) {
    return (signed char)2147483660u;  
}

unsigned char uint_to_uchar(void) {
    return (unsigned char)2147483901u;
}


unsigned char implicit(void) {
    return 2147483901u;
}

int one = 1;
int six = 6;
int three = 3;
int one_twenty_eight = 128;

int main(void) {
    

    
    if (long_to_int() != 1234) {
        return 1;
    }
    if (long_to_uint() != 1234u) {
        return 2;
    }

    
    if (long_to_char() != -one) {
        return 3;
    }

    
    if (long_to_schar() != -one_twenty_eight) {
        return 4;
    }

    
    if (long_to_uchar() != 255) {
        return 5;
    }

    

    
    if (ulong_to_int() != -one) {
        return 6;
    }
    if (ulong_to_uint() != 4294967295U) {
        return 7;
    }

    
    if (ulong_to_char() != -one) {
        return 8;
    }

    
    if (ulong_to_schar() != -one_twenty_eight) {
        return 9;
    }

    
    if (ulong_to_uchar() != 255) {
        return 10;
    }

    

    
    if (int_to_char() != -six) {
        return 11;
    }

    
    if (int_to_schar() != -one) {
        return 12;
    }

    
    if (int_to_uchar() != 250) {
        return 13;
    }

    

    
    if (uint_to_char() != -three) {
        return 14;
    }

    
    if (uint_to_schar() != 12) {
        return 15;
    }
    
    if (uint_to_uchar() != 253) {
        return 16;
    }
    if (implicit() != 253) {
        return 17;
    }
    return 0;
}