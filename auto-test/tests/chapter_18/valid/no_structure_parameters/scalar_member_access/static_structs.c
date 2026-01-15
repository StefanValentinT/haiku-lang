



void *malloc(unsigned long size);
int putchar(int ch);
int puts(char *s);




void test_static_local(int a, int b) {
    struct s {
        int a;
        int b;
    };

    static struct s static_struct;
    if (!(static_struct.a || static_struct.b)) {
        puts("zero");
    } else {
        putchar(static_struct.a);
        putchar(static_struct.b);
        putchar('\n');
    }

    static_struct.a = a;
    static_struct.b = b;
}



void test_static_local_pointer(int a, int b) {
    struct s {
        int a;
        int b;
    };

    static struct s *struct_ptr;
    if (!struct_ptr) {
        struct_ptr = malloc(sizeof(struct s));
    } else {
        putchar(struct_ptr->a);
        putchar(struct_ptr->b);
        putchar('\n');
    }

    struct_ptr->a = a;
    struct_ptr->b = b;
}


struct global {
    char x;
    char y;
    char z;
};

struct global g;

void f1(void) {
    g.x = g.x + 1;
    g.y = g.y + 1;
    g.z = g.z + 1;
}

void f2(void) {
    putchar(g.x);
    putchar(g.y);
    putchar(g.z);
    putchar('\n');
}

void test_global_struct(void) {
    g.x = 'A';
    g.y = 'B';
    g.z = 'C';

    f1();
    f2();
    f1();
    f2();
}


struct global *g_ptr;

void f3(void) {
    g_ptr->x = g_ptr->x + 1;
    g_ptr->y = g_ptr->y + 1;
    g_ptr->z = g_ptr->z + 1;
}

void f4(void) {
    putchar(g_ptr->x);
    putchar(g_ptr->y);
    putchar(g_ptr->z);
    putchar('\n');
}

void test_global_struct_pointer(void) {
    g_ptr = &g;  
    f3();
    f4();
    f3();
    f4();
    
    g_ptr = malloc(sizeof(struct global));
    g_ptr->x = 'a';
    g_ptr->y = 'b';
    g_ptr->z = 'c';
    f3();
    f4();
    f3();
    f4();
}

int main(void) {
    test_static_local('m', 'n');
    test_static_local('o', 'p');
    test_static_local('!', '!');
    ;  
    test_static_local_pointer('w', 'x');
    test_static_local_pointer('y', 'z');
    test_static_local_pointer('!', '!');
    ;  
    test_global_struct();
    test_global_struct_pointer();
    return 0;
}