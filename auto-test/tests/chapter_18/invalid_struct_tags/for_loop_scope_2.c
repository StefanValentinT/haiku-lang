

int main(void) {
    void *ptr;

    
    
    
    
    for (;; ((struct s *)ptr)->i) {
        struct s {
            int i;
        };
        struct s x = {1};
        ptr = &x;
    }
}