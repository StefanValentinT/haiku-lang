/* Test that we can propagate all arithmetic types, including doubles,
 * long and unsigned integers, and characters.
 * */


int target(void) {
    
    double d = 1500.0;
    double d2 = d;

    int sum = (int)(d + d2);  

    
    char c = 250;  
    char c2 = c;
    sum = sum + (c2 + c);  

    
    unsigned char uc = -1;  
    unsigned char uc2 = uc;
    sum = sum + uc + uc2;  

    
    unsigned long ul = 18446744073709551615UL;  
    unsigned long ul2 = ul + 3ul;               
    sum = sum + ul2;                            

    return sum;  
}

int main(void) {
    return target() == 3500;
}