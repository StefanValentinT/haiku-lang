#ifdef SUPPRESS_WARNINGS
#ifdef __clang__
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"
#else
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"
#endif
#endif


int strcmp(char* s1, char* s2);
void exit(int status);
void *malloc(unsigned long size);






union one_double {
    double d1;
    double d2;
};


struct has_union_with_double {
    union one_double member;
};


union has_struct_with_double {
    struct has_union_with_double s;
    double arr[1];
};





union one_int {
    double d;
    char c;
};


union one_int_nested {
    union one_int oi;
    union one_double od;
};


union char_int_mixed {
    char arr[7];
    union char_int_mixed* union_ptr;
    unsigned int ui;
};


union char_int_short {
    char c;
    int i;
};

struct has_union {
    unsigned int i;
    union char_int_short u;
};


union has_struct_with_ints {
    double d;
    struct has_union s;
    unsigned long ul;
};






union two_doubles {
    double arr[2];
    double single;
};


union has_xmm_union {
    union one_double u;
    union two_doubles u2;
};


struct dbl_struct {
    union one_double member1; 
    double member2; 
};


union has_dbl_struct {
    struct dbl_struct member1;
};






union char_arr {
    char arr[11];
    int i;
};



union two_arrs {
    double dbl_arr[2];
    long long_arr[2];
};


union two_eightbyte_has_struct {
    int arr[3]; 
    struct dbl_struct member1; 
};


struct char_first_eightbyte {
    char c;
    double d;
};

struct int_second_eightbyte {
    double d;
    int i;
};

union two_structs {
    
    struct char_first_eightbyte member1;
    
    struct int_second_eightbyte member2;
};



struct nine_bytes {
    int i;
    char arr[5];
};

union has_nine_byte_struct {
    char c;
    long l;
    struct nine_bytes s;
};


union uneven {
    char arr[5];
    unsigned char uc;
};

struct has_uneven_union {
    int i;
    union uneven u;
};


union has_other_unions {
    union uneven u;
    union two_doubles d;
    union has_nine_byte_struct n;
};


union union_array {
    union one_int u_arr[2];
};

union uneven_union_array {
    union uneven u_arr[2];
};



struct small {
    char arr[3];
    signed char sc;
};

union has_small_struct_array {
    struct small arr[3];
};




union gp_and_xmm {
    double d_arr[2]; 
    char c; 
};



union scalar_and_struct {
    long* ptr; 
    struct char_first_eightbyte cfe; 
};


struct has_two_unions {
    union char_int_mixed member1;
    union one_double member2;
};



union small_struct_arr_and_dbl {
    struct small arr[2];
    union two_doubles d;
};



union xmm_and_gp {
    double d;
    struct int_second_eightbyte ise;
};


union xmm_and_gp_nested {
    union xmm_and_gp member1;
    double arr[2];
    union two_doubles d;
};




union lotsa_doubles {
    double arr[3];
    int i;
};

union lotsa_chars {
    char more_chars[18];
    char fewer_chars[5];
};




struct large {
    int i;
    double d;
    char arr[10];
};

union contains_large_struct {
    int i;
    unsigned long ul;
    struct large l;
};


union contains_union_array {
    union gp_and_xmm arr[2];
};




int test_one_double(union one_double u);
int test_has_union_with_double(struct has_union_with_double s);
int test_has_struct_with_double(union has_struct_with_double u);
int test_one_int(union one_int u);
int test_one_int_nested(union one_int_nested u);
int test_char_int_mixed(union char_int_mixed u);
int test_has_union(struct has_union s);
int test_has_struct_with_ints(union has_struct_with_ints u);
int test_two_doubles(union two_doubles u);
int test_has_xmm_union(union has_xmm_union u);
int test_dbl_struct(struct dbl_struct s);
int test_has_dbl_struct(union has_dbl_struct u);
int test_char_arr(union char_arr u);
int test_two_arrs(union two_arrs u);
int test_two_eightbyte_has_struct(union two_eightbyte_has_struct u);
int test_two_structs(union two_structs u);
int test_has_nine_byte_struct(union has_nine_byte_struct u);
int test_has_uneven_union(struct has_uneven_union s);
int test_has_other_unions(union has_other_unions u);
int test_union_array(union union_array u);
int test_uneven_union_array(union uneven_union_array u);
int test_has_small_struct_array(union has_small_struct_array u);
int test_gp_and_xmm(union gp_and_xmm u);
int test_scalar_and_struct(union scalar_and_struct u);
int test_has_two_unions(struct has_two_unions s);
int test_small_struct_arr_and_dbl(union small_struct_arr_and_dbl u);
int test_xmm_and_gp(union xmm_and_gp u);
int test_xmm_and_gp_nested(union xmm_and_gp_nested u);
int test_lotsa_doubles(union lotsa_doubles u);
int test_lotsa_chars(union lotsa_chars u);
int test_contains_large_struct(union contains_large_struct u);
int test_contains_union_array(union contains_union_array u);


int pass_unions_and_structs(int i1, int i2, struct has_union one_gp_struct,
    double d1, union two_doubles two_xmm, union one_int one_gp, int i3, int i4,
    int i5);
int pass_gp_union_in_memory(union two_doubles two_xmm,
    struct has_union one_gp_struct, int i1, int i2, int i3,
    int i4, int i5, int i6, union one_int one_gp);
int pass_xmm_union_in_memory(double d1, double d2, union two_doubles two_xmm,
    union two_doubles two_xmm_copy, double d3, double d4,
    union two_doubles two_xmm_2);
int pass_borderline_union(int i1, int i2, int i3, int i4, int i5,
    union char_arr two_gp);
int pass_borderline_xmm_union(union two_doubles two_xmm, double d1, double d2,
    double d3, double d4, double d5, union two_doubles two_xmm_2);
int pass_mixed_reg_in_memory(double d1, double d2, double d3, double d4,
    int i1, int i2, int i3, int i4, int i5, int i6,
    union gp_and_xmm mixed_regs);
int pass_uneven_union_in_memory(int i1, int i2, int i3, int i4, int i5,
    union gp_and_xmm mixed_regs, union one_int one_gp, union uneven uneven);
int pass_in_mem_first(union lotsa_doubles mem, union gp_and_xmm mixed_regs,
    union char_arr two_gp, struct has_union one_gp_struct);


union one_double return_one_double(void);
union one_int_nested return_one_int_nested(void);
union has_dbl_struct return_has_dbl_struct(void);
union two_arrs return_two_arrs(void);
union scalar_and_struct return_scalar_and_struct(void);
union xmm_and_gp return_xmm_and_gp(void);
union contains_union_array return_contains_union_array(void);
union lotsa_chars pass_params_and_return_in_mem(int i1,
    union scalar_and_struct int_and_dbl, union two_arrs two_arrs, int i2,
    union contains_union_array big_union, union one_int_nested oin);
struct has_uneven_union return_struct_with_union(void);