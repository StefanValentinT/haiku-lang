/* String literals decay to char * arrays,
 * and can't initialize pointers to other types.
 * This applies to static pointers too. */
int main(void) {
    
    static signed char *ptr = "foo";
    return 0;
}