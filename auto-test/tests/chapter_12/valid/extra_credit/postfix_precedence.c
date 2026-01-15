/* Test that cast has lower precedence that postfix ++/--
 * This isn't specific to unsigned integers but unsigned conversions
 * make it possible to test.
 */

int main(void) {
    unsigned int ui = 4294967295U;

    
    
    
    
    if (((unsigned long)ui++) != 4294967295U) {
        return 1; 
    }
    if (ui) {
        return 2; 
    }
    return 0; 
}