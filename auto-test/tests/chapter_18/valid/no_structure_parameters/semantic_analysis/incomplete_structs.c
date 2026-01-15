/* Test that our typechecker can handle valid declarations and expressions
 * involving incomplete structure types
 * */


void *malloc(unsigned long size);
void *calloc(unsigned long nmemb, unsigned long size);
int puts(char *s);
int strcmp(char *s1, char *s2);




struct never_used;
struct never_used incomplete_fun(struct never_used x);



int test_block_scope_forward_decl(void) {
    struct s;             
    struct s *s_ptr = 0;  

    struct s {
        int x;
        int y;
    };  

    
    struct s val = {1, 2};
    s_ptr = &val;
    if (s_ptr->x != 1 || s_ptr->y != 2) {
        return 0;
    }

    return 1;  
}



struct pair;  


struct pair *make_struct(void);
int validate_struct(struct pair *ptr);

int test_file_scope_forward_decl(void) {
    
    struct pair *my_struct = make_struct();
    return validate_struct(my_struct);
    
}


struct pair {
    long l;
    long m;
};


struct pair *make_struct(void) {
    struct pair *retval = malloc(sizeof(struct pair));
    retval->l = 100;
    retval->m = 200;
    return retval;
}

int validate_struct(struct pair *ptr) {
    return (ptr->l == 100 && ptr->m == 200);
}




struct msg_holder;
void print_msg(struct msg_holder *param);
int validate_incomplete_var(void);


extern struct msg_holder incomplete_var;

int test_incomplete_var(void) {
    
    print_msg(&incomplete_var);
    return validate_incomplete_var();
}


struct msg_holder {
    char *msg;
};


int validate_incomplete_var(void) {
    if (strcmp(incomplete_var.msg, "I'm a struct!")) {
        return 0;
    }

    return 1;  
}


struct msg_holder incomplete_var = {"I'm a struct!"};


void print_msg(struct msg_holder *param) {
    puts(param->msg);
}



int test_deref_incomplete_var(void) {
    struct undefined_struct;
    struct undefined_struct *ptr = malloc(4);
    
    
    return &*ptr == ptr;
}





struct opaque_struct;

struct opaque_struct *use_struct_pointers(struct opaque_struct *param) {
    if (param == 0) {
        puts("empty pointer!");
    }
    return 0;
}

int test_use_incomplete_struct_pointers(void) {
    
    struct opaque_struct *ptr1 = calloc(1, 4);
    struct opaque_struct *ptr2 = calloc(1, 4);

    
    
    char *ptr1_bytes = (char *)ptr1;
    if (ptr1_bytes[0] || ptr1_bytes[1]) {
        return 0;
    }

    
    if (ptr1 == 0 || ptr2 == 0 || ptr1 == ptr2) {
        return 0;
    }

    
    static int flse = 0;
    struct opaque_struct *ptr3 = flse ? ptr1 : ptr2;
    if (ptr3 != ptr2) {
        return 0;
    }

    
    if (use_struct_pointers(ptr3)) {
        return 0;
    }

    return 1;  
}

int main(void) {
    if (!test_block_scope_forward_decl()) {
        return 2;
    }

    if (!test_file_scope_forward_decl()) {
        return 3;
    }

    if (!test_incomplete_var()) {
        return 4;
    }

    if (!test_deref_incomplete_var()) {
        return 5;
    }

    if (!test_use_incomplete_struct_pointers()) {
        return 6;
    }

    return 0;  
}