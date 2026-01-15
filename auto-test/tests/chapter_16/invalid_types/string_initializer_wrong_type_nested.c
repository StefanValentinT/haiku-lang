/* String literals can only initialize char arrays,
 * not arrays of other types. This also applies to nested arrays. */
int main(void)
{
    
    
    unsigned int nested[1][2] = {"a"};
    return 0;
}