/* Test that we recognize that a unary instruction uses its operand;
 * i.e. negl %a makes a live. Don't inspect assembly, just validate behavior.
 * NOTE: only works as intended after we've implemented register coalescing.
 * TODO consider using a common template for this and bin_uses_operand
 * */


int glob = 1;

int target(void) {
    int a = 0;

    
    
    if (id(1)) {
        a = id(100);
    }

    
    
    if (id(1)) {
        
        
        
        
        
        
        
        glob = a + glob;

        
        
        
        
        a = -a;
    }
    check_one_int(a, -100);
    check_one_int(glob, 101);
    return 0;
}

int main(void) {
    return target();
}