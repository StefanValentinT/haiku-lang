/* Test that in the expression &*e, we just evaluate e and ignore the & and *.
 * This is why &*null_ptr is valid, even though dereferencing a null pointer
 * would normally produce a runtime error
 */
int main(void) {
    int *null_ptr = 0;
    if (&*null_ptr != 0) 
        return 1;

    
    int **ptr_to_null = &null_ptr;

    
    
    if (&**ptr_to_null)
        return 2;

    return 0;
}