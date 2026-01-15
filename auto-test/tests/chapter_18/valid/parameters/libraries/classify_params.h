/* Test that we classify structure parameters correctly,
 * by passing a variety of structures as arguments.
 * Each test function takes only one argument.
 * */

#ifdef SUPPRESS_WARNINGS
#ifdef __clang__
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#else
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#endif
#endif

int strcmp(char *s1, char *s2);


struct twelve_bytes {
    int i;
    char arr[8];
};  


struct inner {
    int i;
    char ch2;
};

struct nested_ints {
    char ch1;
    struct inner nested;
};  


struct flattened_ints {
    char c;
    int i;
    char a;
};  


struct large {
    int i;
    double d;
    char arr[10];
};  


struct two_ints {
    int i;
    int i2;
};  

struct nested_double {
    double array[1];
};  

struct two_eightbytes {
    double d;
    char c;
};  


struct pass_in_memory {
    double w;
    double x;
    int y;
    long z;
};  


int test_twelve_bytes(struct twelve_bytes s);
int test_nested_ints(struct nested_ints s);
int test_flattened_ints(struct flattened_ints s);
int test_large(struct large s);
int test_two_ints(struct two_ints s);
int test_nested_double(struct nested_double s);
int test_two_eightbytes(struct two_eightbytes s);
int test_pass_in_memory(struct pass_in_memory s);