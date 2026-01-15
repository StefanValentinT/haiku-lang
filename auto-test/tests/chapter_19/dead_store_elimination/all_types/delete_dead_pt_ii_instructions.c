/* Make sure we can delete type conversions, load, and other instructions
 * from Part II when they're dead stores
 * */


long l = 1l;
int i = 2;
unsigned int u = 30u;

struct s {
    int a;
    int b;
    int c;
};

int target(void) {
    
    long x = (long) i; 
    unsigned long y = (unsigned long) u; 
    double d = (double) y + (double) i; 
    x = (long) d; 
    y = (unsigned long) d; 
    int arr[3] = {1, 2, 3}; 
    int j = arr[2]; 
    int *ptr = &i; 
    char c = (char)l; 
    struct s my_struct = {0, 0, 0};
    j = my_struct.b; 
    d = -d * 5.0; 
    return 5;
}

int main(void) {
    return target();
}