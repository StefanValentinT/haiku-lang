struct s {
    int a;
};

int main(void) {
    struct s;  
    struct s *x;
    x->a = 10;  
    return 0;
}