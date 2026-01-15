/* Test that we resolve struct tags wherever they appear:
 * In function, member, and variable declarations,
 * for loop headers, cast expressions, sizeof, derived types
 * and does nothing if one is already in scope?
 * */

void *calloc(unsigned long nmemb, unsigned long size);
void *malloc(unsigned long size);


struct s {
    int a;
};



int test_var_declaration(void) {
    struct shadow {
        int x;
    };
    struct shadow outer;
    outer.x = 2;
    {
        
        struct shadow {
            int y;
        };

        
        struct shadow inner;

        
        
        inner.y = 3;
        if (outer.x != 2) {
            return 0;
        }

        if (inner.y != 3) {
            return 0;
        }
    }

    return 1;  
}


int test_member_declaration(void) {
    struct s {
        int b;
        
        
        struct s *self_ptr;
    };

    struct s my_struct = {123, 0};

    
    
    my_struct.self_ptr = &my_struct;
    if (my_struct.self_ptr->b != 123) {
        return 0;
    }

    return 1;  
}


int test_function_declaration(void) {
    
    struct s outer_struct = {1};
    {
        
        struct s {
            int arr[40];
        };
    }

    
    
    
    struct s *copy_struct(struct s * arg);

    
    struct s *copy = copy_struct(&outer_struct);
    if (copy->a != outer_struct.a) {
        return 0;
    }

    return 1;  
}

struct s *copy_struct(struct s *arg) {
    struct s *ptr = malloc(4);
    ptr->a = arg->a;
    return ptr;
}


int test_for_loop(void) {
    
    for (struct s loop_struct = {10}; loop_struct.a > 0;
         loop_struct.a = loop_struct.a - 1) {
        
        struct s {
            double d;
        };
        static struct s loop_body_struct = {0};

        
        loop_body_struct.d = loop_body_struct.d + 1;

        if (loop_struct.a == 1) {
            
            if (loop_body_struct.d != 10.0) {
                return 0;
            }
        }
    }

    return 1;  
}


int test_cast(void) {
    void *ptr = malloc(10);

    if (ptr) {
        struct s {
            char arr[10];
        };

        
        ((struct s *)ptr)->arr[2] = 10;

        
        char byte = ((char *)ptr)[2];
        if (byte != 10) {
            return 0;
        }
    }

    
    void *second_ptr = malloc(4);

    ((struct s *)second_ptr)->a = 10;
    char lowest_byte = ((char *)second_ptr)[0];
    if (lowest_byte != 10) {
        return 0;
    }

    return 1;  
}


int test_sizeof(void) {
    struct s {
        int a;
        int b;
    };
    struct s x;  
    {
        struct s {
            char arr[15];
        };  

        
        if (sizeof x != 8) {
            return 0;
        };

        if (sizeof(struct s) != 15) {
            return 0;
        }
    }

    
    
    if (sizeof(struct s) != 8) {
        return 0;
    }

    return 1;  
}


int test_derived_types(void) {
    struct s outer_struct = {1};

    
    struct s *(*outer_arr)[3] = calloc(3, sizeof(void *));

    
    struct s {
        int x;
    };

    struct s inner_struct = {2};

    
    struct s *(*inner_arr)[3] = calloc(3, sizeof(void *));

    
    
    outer_arr[0][0] = &outer_struct;
    outer_arr[0][1] = &outer_struct;

    
    
    inner_arr[0][0] = &inner_struct;
    inner_arr[0][2] = &inner_struct;

    if (outer_arr[0][0]->a != 1) {
        return 0;
    }

    if (inner_arr[0][0]->x != 2) {
        return 0;
    }

    return 1;
}



int test_contentless_tag_noop(void) {
    struct s {
        int x;
        int y;
    };

    struct s;

    struct s var;  

    var.x = 10;
    var.y = 11;

    if (var.x != 10 || var.y != 11) {
        return 0;
    }

    return 1;
}

int main(void) {
    if (!test_var_declaration()) {
        return 1;
    }

    if (!test_member_declaration()) {
        return 2;
    }

    if (!test_function_declaration()) {
        return 3;
    }

    if (!test_for_loop()) {
        return 4;
    }

    if (!test_cast()) {
        return 5;
    }

    if (!test_sizeof()) {
        return 6;
    }

    if (!test_derived_types()) {
        return 7;
    }

    if (!test_contentless_tag_noop()) {
        return 8;
    }

    return 0;  
}
