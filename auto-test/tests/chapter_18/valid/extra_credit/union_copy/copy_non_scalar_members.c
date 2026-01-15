


void* calloc(unsigned long nmemb, unsigned long size);

int test_dot(void) {
    
    
    struct struct_with_union my_struct = { {0}, 100000l };
    union simple my_simple_union;
    my_simple_union.l = -1;
    my_struct.u = my_simple_union;

    
    static union complex_union my_union;
    my_union.s = my_struct;

    
    if (my_struct.ul != 100000l || my_struct.u.l != -1) {
        return 0; 
    }

    if (my_union.s.ul != 100000l) {
        return 0; 
    }

    
    my_union.s.u.i = 45;
    
    my_simple_union = my_union.s.u;
    if (my_simple_union.i != 45) {
        return 0; 
    }

    
    static struct struct_with_union another_struct;
    another_struct = my_union.s;
    if (another_struct.ul != 100000l || another_struct.u.i != 45) {
        return 0; 
    }

    return 1; 
}

int test_arrow(void) {
    
    union complex_union* my_union_ptr = calloc(1, sizeof(union complex_union));
    my_union_ptr->u_ptr = calloc(1, sizeof(union has_union));
    my_union_ptr->u_ptr->u_ptr = calloc(1, sizeof(union simple));
    my_union_ptr->u_ptr->u_ptr->i = 987654321;

    
    union has_union another_union = *my_union_ptr->u_ptr;

    
    if (another_union.u_ptr != my_union_ptr->u_ptr->u_ptr || another_union.u_ptr->c != my_union_ptr->u_ptr->u_ptr->c) {
        return 0; 
    }

    
    union simple small_union = { -9999 };
    my_union_ptr->u_ptr->u = small_union;
    if (my_union_ptr->u_ptr->u.i != -9999) {
        return 0; 
    }

    return 1; 
}

int main(void) {
    if (!test_dot()) {
        return 1;
    }

    if (!test_arrow()) {
        return 2;
    }

    return 0; 
}