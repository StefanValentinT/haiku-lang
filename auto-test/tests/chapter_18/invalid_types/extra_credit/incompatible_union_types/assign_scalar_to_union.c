

union u {int a; int b;};

int main(void) {
    union u x = {1};
    x = 2; 
    return 0;
}