/* Make sure static initializers are set to the correct
 * implicitly-converted value at program startup
 */




unsigned int u = 1152921506754330636l;

/* This should be initialized to -2147483646,
 * or 2147483650 - 2^32
 */
int i = 2147483650u;

/* This should be initialized to -9223372036854775716,
 * or 9223372036854775900 - 2^64
 */
long l = 9223372036854775900u; 


long l2 = 2147483650u;


unsigned long ul = 4294967294u;

/* any signed long _literal_ can be converted to an unsigned long w/ no change in value
 * (we don't support negation expressions in constant initializers) */
unsigned long ul2 = 9223372036854775798l;



int i2 = 9223372039002259606ul;



unsigned ui2 = 9223372039002259606ul;

int main(void)
{
    if (u != 2147483660u)
        return 1;
    if (i != -2147483646)
        return 2;
    if (l != -9223372036854775716l)
        return 3;
    if (l2 != 2147483650l)
        return 4;
    if (ul != 4294967294ul)
        return 5;
    if (ul2 != 9223372036854775798ul)
        return 6;
    if (i2 != -2147483498)
        return 7;
    if (ui2 != 2147483798u)
        return 8;
    return 0;
}