/* A union initializer must always have exactly one element,
 * no matter how many members the union has.
 */

union u {
    int a;
    long b;
};

union u x = {1, 2};  

int main(void) {
    return 0;
}
