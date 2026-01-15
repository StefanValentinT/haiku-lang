struct inner {
    int i;
};

struct outer {
    struct inner foo;
};

int main(void) {
    struct outer x = {{1, 2}}; 
    return 0;
}