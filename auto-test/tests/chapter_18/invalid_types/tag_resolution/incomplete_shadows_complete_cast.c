
void *malloc(unsigned long size);
struct s {
    int a;
};

int main(void) {
    void *ptr = malloc(sizeof(struct s));
    struct s;  
    
    
    ((struct s *)ptr)->a = 10;
    return 0;
}