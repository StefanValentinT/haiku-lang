/* Test accessing nested structures members, through dot, arrow, and subscript
 * operators */

void *calloc(unsigned long nmemb, unsigned long size);
void *malloc(unsigned long size);

struct inner {
    double a;
    char b;
    int *ptr;
};

struct outer {
    unsigned long l;
    struct inner *in_ptr;
    struct inner in_array[4];
    int bar;
    struct inner in;
};

int ptr_target;  
                 

int test_auto_dot(void) {
    
    
    struct outer s;

    
    s.in.a = 1.0;
    s.in.b = 2;
    s.in.ptr = &ptr_target;

    
    if (s.in.a != 1.0 || s.in.b != 2 || s.in.ptr != &ptr_target) {
        return 0;
    }

    
    char *char_ptr = &s.in.b;
    if (*char_ptr != 2) {
        return 0;
    }

    
    *s.in.ptr = 5;
    if (ptr_target != 5) {
        return 0;
    }

    
    s.in.a = s.in.b;
    if (s.in.a != 2.0) {
        return 0;
    }

    return 1;  
}

int test_static_dot(void) {
    
    
    static struct outer s;

    
    s.in.a = 1.0;
    s.in.b = 2;
    s.in.ptr = &ptr_target;

    
    if (s.in.a != 1.0 || s.in.b != 2 || s.in.ptr != &ptr_target) {
        return 0;
    }

    
    char *char_ptr = &s.in.b;
    if (*char_ptr != 2) {
        return 0;
    }

    
    *s.in.ptr = 6;
    if (ptr_target != 6) {
        return 0;
    }

    
    s.in.a = s.in.b;
    if (s.in.a != 2.0) {
        return 0;
    }

    return 1;  
}

int test_auto_arrow(void) {
    
    

    struct inner in;
    struct outer s;
    struct outer *s_ptr = &s;
    s_ptr->in_ptr = &in;

    
    s_ptr->l = 4294967295ul;
    s_ptr->bar = -5;

    
    s_ptr->in_ptr->a = 10.0;
    s_ptr->in_ptr->b = 'x';

    
    s_ptr->in_array->a = 11.0;

    
    (s_ptr->in_array + 3)->a = 12.0;

    
    s_ptr->in_array->ptr = &s_ptr->bar;

    
    if (s_ptr->l != 4294967295ul || s_ptr->bar != -5) {
        return 0;
    }

    
    if (s_ptr->in_ptr->a != 10.0 || s_ptr->in_ptr->b != 'x' ||
        s_ptr->in_array->a != 11.0 || (s_ptr->in_array + 3)->a != 12.0) {
        return 0;
    }

    
    char *char_ptr = &s_ptr->in_ptr->b;
    if (*char_ptr != 'x') {
        return 0;
    }

    
    *s_ptr->in_array->ptr = 123;  
    if (s_ptr->bar != 123) {
        return 0;
    }

    
    s_ptr->in_array->b = s_ptr->in_ptr->b;
    if (s_ptr->in_array[0].b != 'x') {
        return 0;
    }

    return 1;  
}

int test_static_arrow(void) {
    
    

    static struct inner in;
    static struct outer s;

    
    static struct outer *s_ptr;
    s_ptr = &s;

    s_ptr->in_ptr = &in;

    
    s_ptr->l = 4294967295ul;
    s_ptr->bar = -5;

    
    s_ptr->in_ptr->a = 10.0;
    s_ptr->in_ptr->b = 'x';

    
    s_ptr->in_array->a = 11.0;

    
    (s_ptr->in_array + 3)->a = 12.0;

    
    s_ptr->in_array->ptr = &s_ptr->bar;

    
    if (s_ptr->l != 4294967295ul || s_ptr->bar != -5) {
        return 0;
    }

    
    if (s_ptr->in_ptr->a != 10.0 || s_ptr->in_ptr->b != 'x' ||
        s_ptr->in_array->a != 11.0 || (s_ptr->in_array + 3)->a != 12.0) {
        return 0;
    }

    
    char *char_ptr = &s_ptr->in_ptr->b;
    if (*char_ptr != 'x') {
        return 0;
    }

    
    *s_ptr->in_array->ptr = 123;  
    if (s_ptr->bar != 123) {
        return 0;
    }

    
    s_ptr->in_ptr->b = s_ptr->in_ptr->a;
    if (s_ptr->in_ptr->b != 10) {
        return 0;
    }

    return 1;  
}

int test_mixed(void) {
    
    
    struct inner *in_ptr = malloc(sizeof(struct inner));
    struct outer out;
    out.in_ptr = in_ptr;
    struct outer *out_ptr = &out;

    
    out.l = 10;
    out.bar = 20;

    
    out.in_ptr->a = -1.0;
    out.in_ptr->b = '!';
    out.in_ptr->ptr = 0;  

    
    out_ptr->in_array[0].a = -2.0;
    out_ptr->in_array[0].b = '?';
    out_ptr->in_array[0].ptr = 0;  
    
    out_ptr->in_array[3].a = -3.0;
    out_ptr->in_array[3].b = '*';
    out_ptr->in_array[3].ptr = malloc(sizeof(int));

    out_ptr->in.a = -3.0;
    out_ptr->in.b = '&';
    int i = 9;
    out_ptr->in.ptr = &i;

    
    if (out.l != 10 || out.bar != 20) {
        return 0;
    }

    
    if (out.in_ptr->a != -1.0 || out.in_ptr->b != '!' || out.in_ptr->ptr) {
        return 0;
    }

    
    if (out_ptr->in_array[0].a != -2.0 || out_ptr->in_array[0].b != '?' ||
        out_ptr->in_array[0].ptr || out_ptr->in_array[3].a != -3.0 ||
        out_ptr->in_array[3].b != '*' || out_ptr->in.a != -3.0 ||
        out_ptr->in.b != '&' || out_ptr->in.ptr != &i) {
        return 0;
    }

    
    *out_ptr->in_array[3].ptr = 5;
    if (*out_ptr->in_array[3].ptr != 5) {
        return 0;
    }

    
    out_ptr->in.b = out.in_ptr->b;
    if (out_ptr->in.b != out.in_ptr->b) {
        return 0;
    }

    return 1;  
}

int test_array_of_structs(void) {
    
    

    static struct outer struct_array[3];
    struct inner *in_ptr = malloc(sizeof(struct inner));

    
    
    struct_array[0].in_ptr = in_ptr;
    struct_array[1].in_ptr = in_ptr;

    
    struct_array[0].in_ptr->a = 20.0;
    struct_array[1].in_ptr->b = '@';
    struct_array[0].in_ptr->ptr = 0;

    struct_array[1].in_array[1].a = 30.0;
    struct_array[1].in_array[0].b = '#';

    struct_array[2].in.a = 40.0;
    struct_array[2].in.b = '$';

    

    
    
    
    if (struct_array[1].in_ptr->a != 20.0 || struct_array[0].in_ptr->b != '@' ||
        struct_array[1].in_ptr->ptr) {
        return 0;
    }

    if (struct_array[1].in_array[1].a != 30.0 ||
        struct_array[1].in_array[0].b != '#' || struct_array[2].in.a != 40.0 ||
        struct_array[2].in.b != '$') {
        return 0;
    }

    return 1;  
}

int test_array_of_struct_pointers(void) {
    
    

    struct outer *ptr_array[2];

    ptr_array[0] = calloc(1, sizeof(struct outer));
    ptr_array[1] = calloc(1, sizeof(struct outer));

    
    

    
    ptr_array[1]->in_ptr = calloc(1, sizeof(struct inner));
    ptr_array[1]->in_ptr->ptr = 0;
    ptr_array[1]->in_ptr->b = '%';
    ptr_array[1]->in_ptr->a = 876.5;

    ptr_array[1]->in_array[2].a = 1000.5;

    ptr_array[1]->in.a = 7e6;

    
    ptr_array[0]->in_ptr = calloc(1, sizeof(struct inner));
    ptr_array[0]->in_ptr->ptr = 0;
    ptr_array[0]->in_ptr->b = '^';
    ptr_array[0]->in_ptr->a = 123.4;

    ptr_array[0]->in_array[1].b = '&';

    
    ptr_array[0]->in.ptr = &ptr_array[0]->bar;

    
    
    ptr_array[0]->bar = 900;

    
    if (ptr_array[0]->in_array[1].b != '&') {
        return 0;
    }

    if (ptr_array[0]->in_ptr->a != 123.4 || ptr_array[0]->in_ptr->b != '^' ||
        ptr_array[0]->in_ptr->ptr) {
        return 0;
    }

    
    if (ptr_array[1]->in.a != 7e6) {
        return 0;
    }

    if (ptr_array[1]->in_array[2].a != 1000.5) {
        return 0;
    }

    if (ptr_array[1]->in_ptr->a != 876.5 || ptr_array[1]->in_ptr->b != '%' ||
        ptr_array[1]->in_ptr->ptr) {
        return 0;
    }

    
    if (*ptr_array[0]->in.ptr != 900) {
        return 0;
    }

    
    

    
    if (ptr_array[0]->l) {
        return 0;
    }
    for (int i = 0; i < 4; i = i + 1) {
        
        struct inner *elem_ptr = &ptr_array[0]->in_array[i];
        if (elem_ptr->a || elem_ptr->ptr) {
            return 0;
        }

        if (elem_ptr->b && i != 1) {
            return 0;
        }
    }

    if (ptr_array[0]->in.a || ptr_array[0]->in.b) {
        return 0;
    }

    
    if (ptr_array[1]->l || ptr_array[1]->bar) {
        return 0;
    }

    for (int i = 0; i < 4; i = i + 1) {
        
        struct inner *elem_ptr = &ptr_array[1]->in_array[i];
        if (elem_ptr->b || elem_ptr->ptr) {
            return 0;
        }

        if (elem_ptr->a && i != 2) {
            return 0;
        }
    }

    if (ptr_array[1]->in.b || ptr_array[1]->in.ptr) {
        return 0;
    }

    return 1;  
}

int main(void) {
    if (!test_auto_dot()) {
        return 1;
    }

    if (!test_static_dot()) {
        return 2;
    }

    if (!test_auto_arrow()) {
        return 3;
    }

    if (!test_static_arrow()) {
        return 4;
    }

    if (!test_mixed()) {
        return 5;
    }

    if (!test_array_of_structs()) {
        return 6;
    }

    if (!test_array_of_struct_pointers()) {
        return 7;
    }

    return 0;
}