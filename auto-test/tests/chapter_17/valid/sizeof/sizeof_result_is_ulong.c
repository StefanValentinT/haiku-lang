/* Test that sizeof expression results in an unsigned long */


int main(void) {

    
    if (sizeof sizeof (char) != 8) {
        return 1;
    }

    
    
    
    
    if (sizeof 4 - sizeof 4 - 1 < 0) {
        return 2;
    }

    return 0;
}