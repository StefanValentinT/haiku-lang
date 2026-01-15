
struct s {
    int i;
};

int main(void) {
    struct s my_struct = {1};
    --my_struct;
    return 0;
}