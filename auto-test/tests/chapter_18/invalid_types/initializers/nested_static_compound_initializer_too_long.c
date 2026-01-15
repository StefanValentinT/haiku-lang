struct inner {
    int i;
};

struct outer {
    struct inner foo;
};

struct outer x = {{1, 2}}; 
