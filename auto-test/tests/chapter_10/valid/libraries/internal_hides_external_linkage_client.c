/* A variable with internal linkage will hide a variable with the same name
 * in a different file, even if the variable in the other file has external linkage.
 */

static int x = 1;


int read_internal_x(void);


int read_x(void);

int main(void) {
    
    
    extern int x;
    if (x != 1)
        return 1;
    
    x = 2;

    if (read_internal_x() != 2)
        return 1;

    
    if (read_x() != 10)
        return 1;
    return 0;
}


extern int x;

int read_internal_x(void) {
    return x;

}