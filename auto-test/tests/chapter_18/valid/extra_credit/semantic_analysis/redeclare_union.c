
int main(void) {
    union u {
        int a;
    };

    union u; 

    union u my_union = {1};
    return my_union.a;
}