#ifdef SUPPRESS_WARNINGS
#ifdef __clang__
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#else
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#endif
#endif

int strcmp(char* s1, char* s2);


union simple {
    int i;
    char c;
    double d;
};

extern union simple s;
int validate_simple(void);


union has_union {
    union simple u;
    char c;
};

extern union has_union h;
int validate_has_union(void);



struct has_union_array {
    union has_union union_array[4];
    char c;
    union simple s;
};


extern struct has_union_array my_struct;
int validate_has_union_array(void);





extern union has_union all_zeros;
int validate_uninitialized(void);



union with_padding {
    char arr[13];
    long l;
}; 

extern union with_padding padded_union_array[3];
int validate_padded_union_array(void);