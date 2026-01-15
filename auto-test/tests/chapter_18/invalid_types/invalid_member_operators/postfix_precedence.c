int main(void) {
    struct s {
        int a;
    };
    struct s x = {10};
    
    
    
    
    return &x->a;
}