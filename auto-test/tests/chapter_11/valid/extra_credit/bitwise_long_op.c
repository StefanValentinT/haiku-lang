/* Test bitwise &, |, and ^ operations on long integers.
 * Make sure we:
 * - promote both operands to a common type;
 * - actually perform quadword (not longword) operations
 * - use appropriate rewrite rules where one operand is an
 *   immediate that can't fit in a signed 32-bit integer
 */
int main(void) {
    
    long l1 = 71777214294589695l;  
    long l2 = -4294967296;  

    if ((l1 & l2) != 71777214277877760l /* 0x00ff_00ff_0000_0000 */) {
        return 1;
    }

    if ((l1 | l2) != -4278255361 /* 0xffff_ffff_00ff_00ff */) {
        return 2;
    }

    if ((l1 ^ l2) != -71777218556133121 /* 0xff00_ff00_00ff_00ff */) {
        return 3;
    }

    /* Rewrite rules: andq $IMM, m64 doesn't work if $IMM can't fit
     * in signed 32-bit int. Ditto for orq and xorq */
    if ((-1l & 34359738368l) != 34359738368l) {  
        return 4;
    }

    if ((0l | 34359738368l) != 34359738368l) {
        return 5;
    }

    
    if ((34359738368l ^ 137438953472l) != 171798691840l) {
        return 6;
    }

    /* Typechecking: promote both operands to common type */
    long l = 4611686018427387903l;  
    
    
    int i = -1073741824;  
    int i2 = -1;

    
    
    
    if ((i & l) != 4611686017353646080l) {
        return 7;
    }

    
    if ((l | i) != -1) {
        return 8;
    }

    
    if ((l ^ i) != -4611686017353646081) {
        return 9;
    }

    
    
    
    if ((i2 ^ 4611686018427387903l) != ~4611686018427387903l) {
        return 10;
    }

    return 0;  
}