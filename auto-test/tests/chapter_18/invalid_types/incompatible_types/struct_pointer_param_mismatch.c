struct s1 {
    int a;
};

struct s2 {
    int a;
};

int get_a(struct s1 *ptr) {
    return ptr->a;
}

int main(void) {
    struct s2 arg = {1};
    
    return get_a(&arg);
}