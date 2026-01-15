

int main(void) {
    int i = 100;
    int *ptr = &i;
    int *ptr2 = &(*ptr -= 10);
    return 0;
}