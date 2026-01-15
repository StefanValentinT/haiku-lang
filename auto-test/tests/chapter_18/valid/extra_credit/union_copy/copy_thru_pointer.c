



int strcmp(char* s1, char* s2);


int test_copy_to_pointer(void) {
    union simple y;
    y.l = -20;
    union simple* x = malloc(sizeof(union simple));
    *x = y;

    
    if (x->l != -20 || x->i != -20 || x->uc_arr[0] != 236 || x->uc_arr[1] != 255 || x->uc_arr[2] != 255) {
        return 0; 
    }

    return 1;  
}


int test_copy_from_pointer(void) {
    
    struct simple_struct my_struct = { 8223372036854775807l, 20e3, 2147483650u };
    static union has_struct my_union;
    my_union.s = my_struct;

    
    union has_struct* union_ptr;
    union_ptr = &my_union;

    
    union has_struct another_union = *union_ptr;

    
    if (another_union.s.l != 8223372036854775807l || another_union.s.d != 20e3 || another_union.s.u != 2147483650u) {
        return 0; 
    }

    return 1;
}





union with_padding {
    char arr[10];
    unsigned int ui;
};

int test_copy_array_members(void) {

    
    union with_padding union_array[3] = { {"foobar"}, {"hello"}, {"itsaunion"} };

    
    union with_padding another_union = union_array[0];
    union with_padding yet_another_union = { "blahblah" };

    
    union_array[2] = yet_another_union;

    
    if (strcmp(union_array[0].arr, "foobar") || strcmp(union_array[1].arr, "hello") || strcmp(union_array[2].arr, "blahblah")) {
        return 0; 
    }

    if (strcmp(another_union.arr, "foobar")) {
        return 0; 
    }

    
    if (strcmp(yet_another_union.arr, "blahblah")) {
        return 0; 
    }

    return 1; 

}

int main(void) {
    if (!test_copy_to_pointer()){
        return 1;
    }

    if (!test_copy_from_pointer()) {
        return 2;
    }

    if (!test_copy_array_members()) {
        return 3;
    }

    return 0; 
}