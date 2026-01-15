/* It's not safe to eliminate a store to one union member if we read another
 * union member later
 */

union u {
    long l;
    int i;
};

int main(void) {
    union u my_union = { -1 };
    
    my_union.l = 180;
    return my_union.i;
}