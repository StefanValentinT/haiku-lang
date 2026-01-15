int main(void)
{
    long x = 10;
    long *ptr = &x + 1;
    long(*array_ptr)[10] = (long (*)[10]) &x;
    
    
    return array_ptr < ptr;
}