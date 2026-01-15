/* Test that we can convert between different pointer types, including pointers to arrays */

int main(void) {

    int simple_array[2] = {1, 2};
    
    int(*ptr_arr[3])[2] = {&simple_array, 0, &simple_array};
    
    
    
    
    
    long *other_ptr = (long *)ptr_arr;

    
    
    return (int(**)[2])other_ptr == ptr_arr;
}