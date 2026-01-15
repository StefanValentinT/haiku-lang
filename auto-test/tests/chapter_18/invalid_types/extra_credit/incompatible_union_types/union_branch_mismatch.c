

int main(void) {
    union u1 {
        int a;
    };
    union u2 {
        int a;
    };
    union u1 x = {10};
    union u2 y = {11};
    1 ? x : y; 
    return 0;
}