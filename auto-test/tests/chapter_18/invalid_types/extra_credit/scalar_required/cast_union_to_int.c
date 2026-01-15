
union u {
    int i;
};

int main(void) {
    union u x = {10};
    return (int)x;
}