/* Make sure we recognize that a function uses some parameter-passing
 * registers, determined by its declaration. Don't inspect assembly,
 * just validate behavior.
 * NOTE: only works as intended after we've implemented register coalescing.
 *
 * This test program is generated from templates/chapter_20_templates/funcall_generates_args.c.jinja
 * */





int f(int a, int b);

int glob = 10;
int x = 0;
int y = 0;
int target(void) {
    int a = glob + 1;
    int b = glob + 2;
    
    
    
    
    
    
    
    
    x = a * glob;
    y = b * glob;
    
    f(a, b);
    
    check_one_int(x, 110);
    check_one_int(y, 120);
    return 0;
}

int main(void) {
    return target();
}