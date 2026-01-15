struct s {
    int a;
};

int main(void) {
    struct outer {
        struct s inner;
    };

    struct outer foo = {{1}};

    
    struct s {
        int b;
    };

    struct outer *ptr = &foo;

    return ptr->inner.b;  
                          
}