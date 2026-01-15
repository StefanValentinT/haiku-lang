

struct s1 {
    int field;
};

struct s2 {
    int field;
};

int main(void) {
    struct s1 a = {1}   ;
    struct s2 b;
    b = a; 
    return b.field;
}