/* When one type declaration shadows another with the same tag (including a
 * union type shadowing struct type or vice versa) you can't specify the outer
 * tag
 * */
int main(void) {
    struct tag {int a;};
    {
        union tag {long l;}; 
        
        
        struct tag *x;
    }
    return 0;
}