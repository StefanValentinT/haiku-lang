/* Make sure we recognize that div makes EAX live.
 * Don't inspect assembly, just validate behavior
 * NOTE: only works as intended once we implement coalescing.
 *
 * This test program is generated from templates/chapter_20_templates/division_uses_ax.c.jinja
 */


int main(void) {
    
    
    unsigned int coalesce_into_eax = unsigned_id(10);

    
    
    
    
    
    unsigned int sum = coalesce_into_eax + 4;

    
    
    
    if (sum != 14) {
        return -1;
    }

    
    
    
    
    
    
    
    unsigned int rem = coalesce_into_eax % 10;

    
    check_one_uint(rem, 0);

    return 0;  
}