/* Test finding the common type of void * and other pointer types (it's always
 * void *) */

void *calloc(unsigned long nmemb, unsigned long size);
void free(void *ptr);

int main(void) {
    
    void *void_ptr = calloc(3, sizeof(unsigned int));

    
    unsigned int array[3] = {1, 2, 3};

    
    if (void_ptr == 0)
        return 1;

    
    if (void_ptr == array)
        return 2;

    
    if (!(void_ptr != array))
        return 3;

    
    
    

    
    static void *null_ptr = 0;
    int *my_array = null_ptr ? void_ptr : array;

    
    
    
    
    int array_element = my_array[1];

    if (array_element != 2) {
        return 4;
    }

    free(void_ptr);
    return 0;
}