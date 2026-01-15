


union u {
    long l;
};

struct has_union {
    int a;
    union u b;
    char c;
};

long some_var = 10l;

struct has_union some_struct = {1,
                                {some_var},  
                                'a'};