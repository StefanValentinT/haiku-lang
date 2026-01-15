struct s {
    int a;
};

union u {
    struct s nested;
};

int main(void) {
    union u my_union = {{1}};
    
    return my_union.a;
}