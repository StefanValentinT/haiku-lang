
union u {
    int a;
    long b;
};
struct s {
    int tag;
    union u contents;
};

struct s my_struct = {
    10,
    {1, 2}  
};