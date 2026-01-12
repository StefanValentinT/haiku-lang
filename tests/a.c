int main(void) {
    int a = 4;
    int pow = 3;

    int count = 0;
    int result = 1;

    while (count < pow) {
        result = result * a;
        count = count + 1;
    }
    return result;
}