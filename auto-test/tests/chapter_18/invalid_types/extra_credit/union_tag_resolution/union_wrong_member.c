union u {
    int a;
};

int main(void) {
    union u foo = {1};

    
    union u {
        int b;
    };

    return foo.b; 
}