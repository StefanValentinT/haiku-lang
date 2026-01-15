/* Test that we recognize that a binary instruction uses its source and
 * destination; e.g. addl %a, %b makes a and b live. Don't inspect assembly,
 * just validate behavior.
 * NOTE: only works as intended after we've implemented register coalescing.
 *
 * This test program is generated from templates/chapter_20_templates/bin_uses_operands.c.jinja
 */



int src_test(int arg) {
    
    
    
    
    
    int x = 5 + arg;
    check_one_int(x, 6);
    return 0;
}

int glob = 1;
int glob2;
int flag = 1;

int dst_test(void) {
    int a = id(100);

    
    
    if (flag) {
        
        
        
        
        
        
        
        glob2 = a + glob;

        
        
        
        
        a = a - 1;
    }

    check_one_int(a, 99);
    check_one_int(glob2, 101);
    return 0;
}

int main(void) {
    src_test(1);
    dst_test();
}