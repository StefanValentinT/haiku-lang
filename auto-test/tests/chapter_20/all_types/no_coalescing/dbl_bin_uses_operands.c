/* Test that we recognize that a binary SSE instruction uses its source and
 * destination; e.g. addsd %a, %b makes a and b live. Don't inspect assembly,
 * just validate behavior.
 * NOTE: only works as intended after we've implemented register coalescing.
 *
 * This test program is generated from templates/chapter_20_templates/bin_uses_operands.c.jinja
 */



double src_test(double arg) {
    
    
    
    
    
    double x = 5 + arg;
    check_one_double(x, 6.0);
    return 0;
}

double glob = 1;
double glob2;
int flag = 1;

int dst_test(void) {
    double a = dbl_id(100.0);

    
    
    if (flag) {
        
        
        
        
        
        
        
        glob2 = a + glob;

        
        
        
        
        a = a / 2.0;
    }

    check_one_double(a, 50.0);
    check_one_double(glob2, 101.0);
    return 0;
}

int main(void) {
    src_test(1);
    dst_test();
}