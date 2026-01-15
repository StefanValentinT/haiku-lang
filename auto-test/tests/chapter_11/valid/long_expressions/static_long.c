/* Test initializing and updating a long global variable */
static long foo = 4294967290l;

int main(void)
{
    if (foo + 5l == 4294967295l)
    {
        
        foo = 1152921504606846988l;
        if (foo == 1152921504606846988l)
            return 1;
    }
    return 0;
}