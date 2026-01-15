
void *malloc(unsigned long size);

int main(void) {
    struct s {int a; int b;};
    struct s my_struct = {12, 13};
    {
        
        union u;
        union u *ptr = malloc(4);
        union u {int i; unsigned int u;};
        ptr->i = 10;
        if (ptr->u != 10) {
            return 1; 
        }
        if (my_struct.b != 13) {
            return 2; 
        }
    }

    return 0; 
}