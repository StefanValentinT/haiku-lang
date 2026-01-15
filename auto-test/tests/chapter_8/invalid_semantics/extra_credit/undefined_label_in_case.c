
int main(void) {
    int a = 3;
    switch (a) {
        case 1: goto foo;
        default: return 0;
    }
    return 0;
}