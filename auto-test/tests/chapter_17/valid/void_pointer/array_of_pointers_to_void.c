/* Test using complex types derived from void
 * arrays of void are illegal, but arrays of pointer to void are allowed */

void *calloc(unsigned long nmemb, unsigned long size);
void free(void *ptr);

int main(void) {
    int i = 10;

    
    
    void *arr[4] = {
        calloc(2, sizeof(int)),  
        &i,                      
        0,                       
        arr  
    };

    
    
    long *l = arr[0];
    if (*l) 
        return 1;

    
    int elem_1_val = *(int *)arr[1];
    if (elem_1_val != 10)
        return 2;

    
    if (arr[2])
        return 3;

    
    if (arr[3] != arr)
        return 4;
    free(arr[0]);  
    return 0;
}