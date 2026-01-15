/* YOu can't declare the same union type twice. */

int main(void) {
    union u {int a;};
    union u {int a;}; 
    return 0;
}