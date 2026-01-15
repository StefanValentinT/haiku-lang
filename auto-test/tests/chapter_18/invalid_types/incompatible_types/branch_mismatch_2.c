struct s {
    int a;
};

int main(void) {
    struct s x = {1};
    
    1 ? x : (void) 2;
}