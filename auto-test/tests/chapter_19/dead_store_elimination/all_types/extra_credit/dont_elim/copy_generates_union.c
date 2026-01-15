/* Reading a sub-object within a union makes the whole union live */

struct s {
    int a;
    int b;
};

union u {
    struct s str;
    long l;
};

union u glob = {{1, 2}};

int main(void) {
    union u my_union;
    my_union = glob; 
    return my_union.str.a;
}