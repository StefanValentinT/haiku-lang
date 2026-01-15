

struct inner {
    char c;
    unsigned int u;
};

struct outer {
    unsigned long l;
    struct inner *in_ptr;
    int array[3];
};

void *calloc(unsigned long nmemb, unsigned long size);

int main(void) {
    struct outer my_struct = {
        
        9223372036854775900ul,
        
        calloc(3, sizeof (struct inner)),
        
        {-1000, -2000, -3000},
    };
    struct outer *my_struct_ptr = &my_struct;

    
    if (++my_struct.l != 9223372036854775901ul) {
        return 1; 
    }

    
    if (--my_struct.in_ptr[0].u != 4294967295U) { 
        return 2; 
    }

    
    if (my_struct.in_ptr->c++) {
        return 3; 
    }

    
    if (my_struct_ptr->array[1]-- != -2000) {
        return 4; 
    }

    
    
    if (my_struct_ptr->l != 9223372036854775901ul) {
        return 5; 
    }

    if (my_struct.in_ptr->c != 1) {
        return 6; 
    }
    if (my_struct_ptr->in_ptr->u !=  4294967295U) {
        return 7; 
    }

    if (my_struct_ptr->array[1] != -2001) {
        return 8; 
    }

    if (my_struct_ptr->array[0] != -1000 || my_struct_ptr->array[2] != -3000) {
        return 9; 
    }

    
    
    my_struct_ptr->in_ptr[1].c = -1;
    my_struct_ptr->in_ptr[1].u = 1u;
    my_struct_ptr->in_ptr[2].c = 'X';
    my_struct_ptr->in_ptr[2].u = 100000u;

    (++my_struct_ptr->in_ptr)->c--; 
    my_struct_ptr->in_ptr++->u++; 

    

    
    if (my_struct_ptr->in_ptr[-2].c != 1 || my_struct_ptr->in_ptr[-2].u != 4294967295U) {
        return 10;
    }

    
    if (my_struct_ptr->in_ptr[-1].c != -2) {
        return 11; 
    }

    if (my_struct_ptr->in_ptr[-1].u != 2) {
        return 12; 
    }

    
    if (my_struct_ptr->in_ptr[0].c != 'X' || my_struct_ptr->in_ptr[0].u != 100000u) {
        return 13; 
    }

    return 0;
}