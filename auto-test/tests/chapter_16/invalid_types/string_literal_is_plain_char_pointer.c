/* String literals decay to char * arrays,
 * and can't initialize pointers to other types. */
int main(void) {
    
    signed char *ptr = "foo";
    return 0;
}