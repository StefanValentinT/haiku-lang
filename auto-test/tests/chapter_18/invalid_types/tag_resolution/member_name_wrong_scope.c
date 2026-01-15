struct s {
    int a;
};

int main(void) {
    struct s foo = {1};

    
    struct s {
        int b;
    };

    return foo.b; 
}