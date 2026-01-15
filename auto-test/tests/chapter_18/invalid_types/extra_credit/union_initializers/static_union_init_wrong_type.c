/* The one element in a union initializer must be compatible with the union's
 * first member.
 */

union u {
    signed char *ptr;
    double d;
};

int main(void) {
    
    static union u my_union = {"A char array"};
}