/* Test that we correctly determine the type, and size, of all constants */

int main(void) {
    
    
    if (sizeof 'a' != 4) {
        return 1;
    }

    
    if (sizeof 2147483647 != 4) {
        return 2;
    }

    
    if (sizeof 4294967295U != 4) {
        return 3;
    }

    
    if (sizeof 2l != 8) {
        return 4;
    }

    
    if (sizeof 0ul != 8) {
        return 5;
    }

    
    if (sizeof 1.0 != 8) {
        return 6;
    }
    return 0;
}