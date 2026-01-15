/* Test that we can declare a function with an incomplete parameter type,
 * then call/define it after the type is completed */
struct s;



int foo(struct s blah);


struct s {
    int a;
    int b;
};

int main(void) {
    struct s arg = {1, 2};
    return foo(arg); 
}

int foo(struct s blah) {
    return blah.a + blah.b;
}