/* Make sure we recognize that at least one of cdq/idiv makes EAX live.
 * (There's no way to test these instructions separately.)
 * Don't inspect assembly, just validate behavior
 * NOTE: only works as intended once we implement coalescing.
 *
 * This test program is generated from templates/chapter_20_templates/division_uses_ax.c.jinja
 */


int main(void) {
    
    
    int coalesce_into_eax = id(10);

    
    
    
    
    
    int sum = coalesce_into_eax + 4;

    
    
    
    if (sum != 14) {
        return -1;
    }

    
    
    
    
    
    
    
    int rem = coalesce_into_eax % 10;

    
    check_one_int(rem, 0);

    return 0;  
}