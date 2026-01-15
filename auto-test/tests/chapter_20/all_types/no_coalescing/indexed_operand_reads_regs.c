/* Using indexed operands of the form (%reg1, %reg2, scale) reads reg1
 * and reg2. The test script just validates this  program's behavior;
 * it doesn't inspect assembly.
 * Note: only works as intended after we've implemented register coalescing.
 * */


int arr[2] = {1, 2};
long arr2[2] = {3, 4};


int three = 3;

int main(void) {
    
    
    
    
    
    
    long one = three - 2;
    long zero = three - 3;
    int *ptr = arr;
    long *ptr2 = arr2;

    
    
    
    
    int *other_ptr = ptr + one;
    
    
    
    
    long *other_ptr2 = ptr2 + zero;

    check_one_int(*other_ptr, 2);
    check_one_long(*other_ptr2, 3);
    return 0;
}
