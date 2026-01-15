/* String literals can only initialize char arrays,
 * not arrays of other types.
 * This also applies to nested static arrays. */
int main(void)
{
    
    
    static long int nested[1][2] = {"a"};
    return 0;
}