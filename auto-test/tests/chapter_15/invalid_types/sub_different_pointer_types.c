int main(void)
{
    long x[10];
    long *ptr = x;
    unsigned long *ptr2 = (unsigned long *)ptr;
    
    return ptr - ptr2;
}