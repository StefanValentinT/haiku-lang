/* It's illegal to specify an array type with any incomplete
 * element type, including union types.
 */

union u;  
int main(void) {
    
    
    union u(*arr)[3];
    return 0;
}