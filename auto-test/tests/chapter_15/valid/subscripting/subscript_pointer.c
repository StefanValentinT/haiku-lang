/* Test that we can apply subscript expressions to all pointers,
 * not just pointers that decayed from arrays */


int subscript_pointer_to_pointer(int **x) {
    return x[0][0];
}

int main(void) {
    int a = 3;
    int *ptr = &a;

    
    if (ptr[0] != 3) {
        return 1;
    }

    
    int **ptr_ptr = &ptr;
    if (ptr_ptr[0][0] != 3) {
        return 2;
    }

    
    
    int dereferenced = subscript_pointer_to_pointer(ptr_ptr);
    if (dereferenced != 3) {
        return 3;
    }
    return 0;
}