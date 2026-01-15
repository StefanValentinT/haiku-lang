/* A function with a mix of int, double, and struct types, with enough
 * register pressure that we need to spill. This tests that we correctly track
 * which registers are used to pass structure types; if we don't track them
 * correctly we'll clobber live registers. Just validate behavior;
 * don't inspect assembly.
 *
 * NOTE: only works as intended once we've implemented coalescing.
 * */


struct s {
    long l;    
    double d;  
};

long glob = 100;
double glob_d = 200.0;

long x = 0;
double y = 0;



int callee(struct s s1, long a, double b);

int main(void) {
    long a = glob + 1;        
    double b = glob_d + 2.0;  

    struct s s1 = {-50, -40.0};

    
    
    
    
    
    
    

    x = a * glob;    
    y = b * glob_d;  

    callee(s1, a, b);
    check_one_long(x, 10100);
    check_one_double(y, 40400.0);
    return 0;
}