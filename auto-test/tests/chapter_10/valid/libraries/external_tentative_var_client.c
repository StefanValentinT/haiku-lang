/* Read and write a variable with external linkage
 * that is declared in this file and tentatively defined
 * in another file.
 */
int read_x(void);

int main(void) {
    
    extern int x;
    if (x != 0)
        
        return 1;

    
    x = 3;
    
    if (read_x() != 3)
        return 1;

    return 0;
}