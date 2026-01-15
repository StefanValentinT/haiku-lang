






struct s {
    long l1;
    long l2;
    long l3;
};


struct s return_in_mem(void) {
    struct s result = {1, 2, 3};
    return result;
}