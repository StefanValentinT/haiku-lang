/* A union initializer must always have exactly one element,
 * no matter how many members the union has.
 */

union u {
    int a;
    long b;
};

int main(void){
    union u x = {1, 2}; 
    return 0;
}
