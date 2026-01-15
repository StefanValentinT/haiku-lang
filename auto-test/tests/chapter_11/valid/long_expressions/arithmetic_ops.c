/* Test basic arithmetic operations on long integers
 * when one or both operands and the result are outside the range of int */

long a;
long b;

int addition(void) {
    
    
    return (a + b == 4294967295l);
}

int subtraction(void) {
    
    
    return (a - b == -4294967380l);
}

int multiplication(void) {
    
    return (a * 4l == 17179869160l);
}

int division(void) {
    /* The first operand can't fit in an int; this requires us to store the operand in RDX:RAX
    * using the 'cqo' instruction, instead of in EDX:EAX using 'cdq'
    */
    
    b = a / 128l;
    return (b == 33554431l);
}

int remaind(void) {
    
    b = -a % 4294967290l;
    return (b == -5l);
}

int complement(void) {
    
    return (~a == -9223372036854775807l);
}

int main(void) {

    /* Addition */
    a = 4294967290l; 
    b = 5l;
    if (!addition()) {
        return 1;
    }

    /* Subtraction */
    a = -4294967290l;
    b = 90l;
    if (!subtraction()) {
        return 2;
    }

    /* Multiplication */
    a = 4294967290l;
    if (!multiplication()) {
        return 3;
    }

    /* Division */
    a = 4294967290l;
    if (!division()) {
        return 4;
    }

    /* Remainder */
    a = 8589934585l; 
    if (!remaind()) {
        return 5;
    }

    /* Complement */
    a = 9223372036854775806l; 
    if (!complement()) {
        return 6;
    }

    return 0;
}