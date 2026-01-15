/* Test that we consider all static variables aliased,
 * so store kills copies to/from these variables */
int stat;

int target(int *stat_ptr) {
    int a = 0;
    a = stat;       
    *stat_ptr = 8;  
    return a;       
}

int main(void) {
    int *ptr = &stat;
    stat = 5;
    int result = target(ptr);
    if (result != 5) {
        return 1;  
    }
    if (stat != 8) {
        return 2;  
    }
    return 0;  
}