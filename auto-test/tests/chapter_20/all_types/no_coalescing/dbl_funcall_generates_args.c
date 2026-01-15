/* Make sure we recognize that a function uses some parameter-passing
 * XMM registers, determined by its declaration. Don't inspect assembly,
 * just validate behavior.
 * NOTE: only works as intended after we've implemented register coalescing.
 *
 * This test program is generated from templates/chapter_20_templates/funcall_generates_args.c.jinja
 * */





int use_dbls(double a, double b);

double glob = 10.0;
double x = 0.0;
double y = 0.0;
int target(void) {
    double a = glob + 1.0;
    double b = glob + 2.0;
    
    
    
    
    
    
    
    
    x = a * glob;
    y = b * glob;
    
    use_dbls(a, b);
    
    check_one_double(x, 110.0);
    check_one_double(y, 120.0);
    return 0;
}

int main(void) {
    return target();
}