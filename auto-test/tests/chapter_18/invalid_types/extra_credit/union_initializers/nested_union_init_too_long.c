/* All union initializers (including nested ones) must have exactly one element */

int main(void) {
    union u {
        double d; int x;
    };
    union u array_of_unions[3] = {
        
        {1.0, 2.0, 3.0}
    };
}