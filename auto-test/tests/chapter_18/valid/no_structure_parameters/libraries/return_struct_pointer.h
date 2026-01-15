/* Test returning struct pointers from functions
 * and using struct pointers returned from functions
 * */

void *malloc(unsigned long size);


struct inner {
    double d;
    int i;
};

struct outer {
    char a;
    char b;
    struct inner substruct;
};

struct outermost {
    int i;
    struct outer *nested_ptr;
    struct outer nested_struct;
};


struct inner *make_struct_inner(int seed);
struct outer *make_struct_outer(int seed);
struct outermost *make_struct_outermost(int seed);