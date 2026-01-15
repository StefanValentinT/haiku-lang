


struct one_elem {
    long l;
};
struct three_elems {
    int one;
    int two;
    int three;
};

union one_or_three_elems {
    struct one_elem a;
    struct three_elems b;
};

int main(void) {
    
    
    static union one_or_three_elems my_union = {{1, 2, 3}};
    return 0;
}