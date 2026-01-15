
void f(void) {
    return;
}

int main(void) {
    int *x = 0;
    x += f();
    return 0;
}