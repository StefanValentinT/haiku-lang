/* Test initialization of non-nested static structs, including:
 * - partial initialization
 * - implicit conversion of scalar elements
 * - array decay of string literals
 */
#ifdef SUPPRESS_WARNINGS
#ifdef __clang__
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#else
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#endif
#endif

int strcmp(char *s1, char *s2);

struct s {
    double one_d;
    char *two_msg;
    unsigned char three_arr[3];
    int four_i;
};


extern struct s uninitialized;
extern struct s partial;
extern struct s partial_with_array;
extern struct s converted;




int test_uninitialized(void);


int test_partially_initialized(void);


int test_partial_inner_init(void);


int test_implicit_conversion(void);