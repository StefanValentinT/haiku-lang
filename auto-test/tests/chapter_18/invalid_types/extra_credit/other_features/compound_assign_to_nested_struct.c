


struct inner {
    int i;
};

struct outer {
    struct inner s;
};

int main(void) {
    struct outer x = {{1}};
    x.s *= 10;
    return 0;
}