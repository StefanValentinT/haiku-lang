
struct s { int i; };
int main(void) {
    int i = 100;
    struct s x = { 100 };
    i += x;
    return 0;
}