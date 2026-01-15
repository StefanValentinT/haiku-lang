/* Test constant folding of sign extension, zero extension, and truncation.
 * We couldn't test this thoroughly during the constant folding phase because
 * we hadn't implemented copy propagation yet.
 * */


/* Sign extension */




long target_extend_int_to_long(void) {
    int i = -1000;
    long l = (long)i;
    return (l - 72057594037927936l) / 3l;  
}



unsigned long target_extend_int_to_ulong(void) {
    int i = -1000;
    unsigned long u = (unsigned long)i;
    return u % 50ul;
}

/* Zero extension */
long target_extend_uint_to_long(void) {
    unsigned int u = 2147483648u;  
    long l = (long)u;
    
    if (l < 0) {
        return 0;  
    }
    return l % 7l;
}

unsigned long target_extend_uint_to_ulong(void) {
    unsigned int u = 4294967295U;
    unsigned long l = (unsigned long)u;
    return (l == 4294967295Ul);
}

/* Truncation */





int target_truncate_long_to_int(void) {
    long l = 9223372036854775807l;         
    int i = (int)l;                        
    long l2 = -9223372036854775807l - 1l;  
    int i2 = (int)l2;                      
    
    
    if (i2) {  
        return 0;
    }
    
    
    
    return 20 / i;
}



unsigned int target_truncate_long_to_uint(void) {
    long l = -9223372032559808513l;  
    unsigned int u = (unsigned)l;    
    if (u - 4294967295U) {           
        return 0;
    }
    return u / 20;
}


int target_truncate_ulong_to_int(void) {
    unsigned long ul = 18446744073709551615UL;  
    int i = (int)ul;                            
    unsigned long ul2 = 9223372039002259456ul;  
    int i2 = (int)ul2;                          
    if (i2 >= 0) {                              
        return 0;
    }
    return 10 / i;  
}


unsigned int target_truncate_ulong_to_uint(void) {
    unsigned long ul = 18446744073709551615UL;  
    unsigned int u = (unsigned int)ul;          
    return u / 20;
}

/* Conversions to/from character types.
 * There are no constants of character type, and chars are promoted
 * to int before almost every operation, so we can't test truncation and
 * extension separately
 * */






int target_char_int_conversion(void) {
    
    int i = 257;
    char c = i;
    i = 255;
    char c2 = i;
    i = 2147483647;  
    signed char c3 = i;
    i = -2147483647 - 1;  
    char c4 = i;
    i = -129;  
               
    signed char c5 = i;
    i = 128;  
              
    char c6 = i;
    
    
    
    if (c != 1) {
        return 1;  
    }
    if (c2 != -1) {
        return 2;  
    }
    if (c3 != -1) {
        return 3;  
    }
    if (c4 != 0) {
        return 4;  
    }
    if (c5 != 127) {
        return 5;  
    }
    if (c6 != -128) {
        return 6;  
    }
    return 0;  
}

int target_uchar_int_conversion(void) {
    int i = 767;
    unsigned char uc1 = i;  
    i = 512;
    unsigned char uc2 = i;  
    i = -2147483647;        
    unsigned char uc3 = i;  
    i = -2147483647 + 127;  
    unsigned char uc4 = i;  

    
    
    if (uc1 != 255) {
        return 1;  
    }
    if (uc2) {
        return 2;  
    }
    if (uc3 != 1) {
        return 3;  
    }
    if (uc4 != 128) {
        return 1;  
    }
    return 0;  
}

int target_char_uint_conversion(void) {
    char c = 2148532223u;              
    signed char c2 = 2147483775u;      
    unsigned int u = (unsigned int)c;  
    if (u != 4294967295U) {
        return 1;  
    }
    u = (unsigned int)c2;
    if (u != 127u) {
        return 2;  
    }
    return 0;
}

int target_uchar_uint_conversion(void) {
    unsigned char uc = 2148532223u;  
    unsigned int ui = (unsigned int)uc;
    if (ui != 255u) {
        return 1;  
    }
    return 0;
}

int target_char_long_conversion(void) {
    long l = 3377699720528001l;  
    char c = l;                  
    l = 9223372036854775807l;    
    char c2 = l;                 
    l = 2147483648l + 127l;      
    signed char c3 = l;          
    l = -2147483647l - 1l;       
    char c4 = l;                 
    l = 2147483648l + 128l;
    signed char c5 = l;  
    
    
    
    if (c != -127l) {
        return 1;  
    }
    if (c2 != -1l) {
        return 2;  
    }
    if (c3 != 127l) {
        return 3;   
    }
    if (c4) {
        return 4;   
    }
    if (c5 != -128l) {
        return 5;   
    }
    return 0;  
}

int target_uchar_long_conversion(void) {
    long l = 255l + 4294967296l;
    unsigned char uc1 = l;            
    l = 36028798092705792l;           
    unsigned char uc2 = l;            
    l = -9223372036854775807l;        
    unsigned char uc3 = l;            
    l = -9223372036854775807l + 127;  
    unsigned char uc4 = l;            

    
    
    if (uc1 != 255) {
        return 1;  
    }
    if (uc2) {
        return 2;  
    }
    if (uc3 != 1) {
        return 3;  
    }
    if (uc4 != 128) {
        return 1;  
    }
    return 0;  
}

int target_char_ulong_conversion(void) {
    char c = 9223373136366403583ul;          
    signed char c2 = 9223372036854775935ul;  
    unsigned long ul = (unsigned long)c;     
    if (ul != 18446744073709551615UL) {
        return 1;  
    }
    ul = (unsigned long)c2;
    if (ul != 127ul) {
        return 2;  
    }
    return 0;
}

int target_uchar_ulong_conversion(void) {
    unsigned char uc =
        9223372037929566207ul;  
    unsigned int ui = (unsigned int)uc;
    if (ui != 255u) {
        return 1;  
    }
    return 0;
}
int main(void) {
    if (target_extend_int_to_long() != -24019198012642978l) {
        return 1;  
    }
    if (target_extend_int_to_ulong() != 16ul) {
        return 2;  
    }
    if (target_extend_uint_to_long() != 2l) {
        return 3;  
    }
    if (target_extend_uint_to_ulong() != 1ul) {
        return 4;  
    }
    if (target_truncate_long_to_int() != -20) {
        return 5;  
    }
    if (target_truncate_long_to_uint() != 214748364u) {
        return 6;  
    }
    if (target_truncate_ulong_to_int() != -10) {
        return 7;  
    }
    if (target_truncate_ulong_to_uint() != 214748364u) {
        return 8;  
    }
    if (target_char_int_conversion()) {
        return 9;  
    }
    if (target_uchar_int_conversion()) {
        return 10;  
    }
    if (target_char_uint_conversion()) {
        return 11;  
    }
    if (target_uchar_uint_conversion()) {
        return 12;  
    }
    if (target_char_long_conversion()) {
        return 13;  
    }
    if (target_uchar_long_conversion()) {
        return 14;  
    }
    if (target_char_ulong_conversion()) {
        return 15;  
    }
    if (target_uchar_ulong_conversion()) {
        return 16;  
    }
    return 0;
}