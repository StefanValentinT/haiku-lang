/* Test copy prop/constant folding of compound bitwise assignment with non-integer
 * types and type conversions
 * TODO: use templates for duplicate code between here and earlier chapters
 * instead of copy-paste (ditto for other extra-credit constant-folding tests too!)
 */


 
 
int target_chars(void) {
    signed char c1 = -128;
    signed char c2 = -120;
    signed char c3 = -2;
    signed char c4 = 1;
    signed char c5 = 120;

    unsigned char u1 = 0;
    unsigned char u2 = 170;
    unsigned char u3 = 250;
    unsigned char u4 = 255;

    
    c1 ^= 12345; 
    c2 |= u4;
    c3 &= u2 - (unsigned char)185;
    c4 <<= 7u; 
    
    
    c5 >>= 31;

    
    long x = 32;
    
    
    u4 <<= 12;
    u3 >>= (x - 1);
    u2 |= -399; 
    x = -4296140120l; 
    u1 ^= x;

    
    if (c1 != -71) {
        return 1; 
    }

    if (c2 != -1) {
        return 2; 
    }

    if (c3 != -16) {
        return 3; 
    }

    if (c4 != -128) {
        return 4; 
    }

    if (c5) {
        return 5; 
    }

    if (u1 != 168) {
        return 6; 
    }

    if (u2 != 251) {
        return 7; 
    }

    if (u3) {
        return 8; 
    }

    if (u4) {
        return 9; 
    }

    return 0;
}




int target_long_bitwise(void) {
    
    long l1 = 71777214294589695l;  
    long l2 = -4294967296;  

    l1 &= l2;
    if (l1 != 71777214277877760l) {
        return 1; 
    }

    l2 |= 100l;
    if (l2 != -4294967196) {
        return 2;
    }

    l1 ^= -9223372036854775807l;
    if (l1 != -9151594822576898047l /* 0x80ff_00ff_0000_0001 */) {
        return 3;
    }

    
    l1 = 4611686018427387903l;  
    int i = -1073741824;  
    
    
    
    
    l1 &= i;
    if (l1 != 4611686017353646080l) {
        return 4;
    }

    
    i = -2147483648l; 
    
    
    
    
    if ((i |= 71777214294589695l) != -2130771713) {
        return 5;
    }
    if (i != -2130771713) {
        return 6;
    }

    return 0; 
}



int target_long_bitshift(void) {
    
    int x = 100;
    x <<= 22l;
    if (x != 419430400) {
        return 1; 
    }

    
    if ((x >>= 4l) != 26214400) {
        return 2; 
    }

    
    if (x != 26214400) {
        return 3;
    }

    
    long l = 12345l;
    if ((l <<= 33) != 106042742538240l) {
        return 4;
    }

    l = -l;
    if ((l >>= 10) != -103557365760l) {
        return 5;
    }

    return 0; 
}


int target_unsigned_bitwise(void) {
    unsigned long ul = 18446460386757245432ul; 
    ul &= -1000; 
    if (ul != 18446460386757244952ul /* 0xfffe_fdfc_fbfa_f818 */) {
        return 1; 
    }

    ul |= 4294967040u; 

    if (ul != 18446460386824683288ul /* 0xfffe_fdfc_ffff_ff18 */) {
        return 2; 
    }

    
    
    
    int i = 123456;
    unsigned int ui = 4042322160u; 
    long l = -252645136; 
    
    
    
    
    if (ui ^= l) {
        return 3; 
    }

    
    if (ui) {
        return 4; 
    }
    
    if (i != 123456) {
        return 5;
    }
    if (l != -252645136) {
        return 6;
    }

    return 0; 
}


int target_unsigned_bitshift(void) {

    
    int i = -2;
    
    
    i >>= 3u;
    if (i != -1) {
        return 1;
    }

    unsigned long ul = 18446744073709551615UL;  
    ul <<= 44;                                  
    if (ul != 18446726481523507200ul) {
        return 2;  
    }
    return 0;  
}

int main(void) {
    if (target_chars()) {
        return 1; 
    }

    if (target_long_bitwise()) {
        return 2; 
    }

    if (target_long_bitshift()) {
        return 3; 
    }

    if (target_unsigned_bitwise()) {
        return 4; 
    }

    if (target_unsigned_bitshift()) {
        return 5; 
    }

    return 0; 
}