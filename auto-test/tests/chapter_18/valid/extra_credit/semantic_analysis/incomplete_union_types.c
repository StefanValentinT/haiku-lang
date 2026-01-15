/* Test that our typechecker can handle valid declarations and expressions
 * involving incomplete union types
 * */


void *calloc(unsigned long nmemb, unsigned long size);
int puts(char *s);

 
 
union never_used;
union never_used incomplete_fun(union never_used x);



int test_block_scope_forward_decl(void) {
    union u;             
    union u* u_ptr = 0;  

    union u {
        long x;
        char y;
    };  

    
    union u val = { -100000000l };
    u_ptr = &val;
    if (u_ptr->x != -100000000l || u_ptr->y != 0) {
        return 0; 
    }

    return 1;  
}


union opaque_union;

union opaque_union* use_union_pointers(union opaque_union* param) {
    if (param == 0) {
        puts("null pointer");
    }

    return 0;
}

int test_use_incomplete_union_pointers(void) {
    
    union opaque_union* ptr1 = calloc(1, 4);
    union opaque_union* ptr2 = calloc(1, 4);

    
    
    char* ptr1_bytes = (char*)ptr1;
    if (ptr1_bytes[0] || ptr1_bytes[1]) {
        return 0;
    }

    
    if (ptr1 == 0 || ptr2 == 0 || ptr1 == ptr2) {
        return 0;
    }

    
    static int flse = 0;
    union opaque_union* ptr3 = flse ? ptr1 : ptr2;
    if (ptr3 != ptr2) {
        return 0;
    }

    
    if (use_union_pointers(ptr3)) {
        return 0;
    }

    return 1;  
}

int main(void) {
    if (!test_block_scope_forward_decl()) {
        return 1; 
    }

    if (!test_use_incomplete_union_pointers()) {
        return 2; 
    }

    return 0; 
}