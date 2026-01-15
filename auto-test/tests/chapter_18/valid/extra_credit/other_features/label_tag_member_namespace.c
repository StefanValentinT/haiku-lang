

int main(void) {
    struct x {
        int x;
    };
    struct x x = {10};
    goto x;
    return 0;
x:
    return x.x; 
}