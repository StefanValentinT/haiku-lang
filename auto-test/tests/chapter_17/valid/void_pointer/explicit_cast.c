/* test explicit casts between void * and other pointer types,
 * and between void * and integer types
 */


void *malloc(unsigned long size);
void free(void *ptr);
void *memcpy(void *s1, void *s2, unsigned long n);

int main(void) {
    

    void *ptr = malloc(4 * sizeof(double));
    
    double *double_ptr = (double *)ptr;
    double_ptr[2] = 10.0;
    
    if ((void *)double_ptr != ptr) {
        return 1;
    }
    double result = double_ptr[2];

    if (result != 10.0) {
        
        return 2;
    }

    
    unsigned long ul = (unsigned long)ptr;
    
    
    if (ul % 8) {
        return 3;
    }

    free(ptr);

    
    long zero = 0;
    ptr = (void *) zero;
    if (ptr) {
        return 4;
    }
    zero = (long) ptr;
    if (zero) {
        return 5;
    }
    return 0;
}
