/* Test standard pointer operations on string literals
 * including pointer arithmetic and subscripting.
 */



int main(void) {
    
    if ("abcdefg"[2] != 'c') {
        return 1;
    }

    
    char *ptr = "This is a string!" + 10;  
    if (*ptr != 's') {
        return 2;
    }

    if (ptr[6] != '!') {
        return 3;
    }

    if (ptr[7]) {  
        return 4;
    }

    
    
    if (!"Not a null pointer!") {
        return 5;
    }
}