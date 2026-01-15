/* The one element in a union initializer must be compatible with the union's
 * first member.
 */

union u {
    long *ptr;
    double d;
};

int main(void) {
    
    
    union u my_union = {1.0};
}