


int main(void) {
    int i = 0;
    long l = 0;
    static char arr[3] = {0, 0, 0};
    char *ptr = arr;
    if (sizeof (i++) != 4) {
        return 1; 
    }

    if (sizeof (arr[0]--) != 1) {
        return 2; 
    }


    if (sizeof (++l) != 8) {
        return 3; 
    }

    if (sizeof (--arr[1]) != 1) {
        return 4; 
    }

    if (sizeof (ptr--) != 8) {
        return 5;
    }

    

    if (i) {
        return 6; 
    }

    if (l) {
        return 7; 
    }

    if (arr[0] || arr[1] || arr[2]) {
        return 8; 
    }

    if (ptr != arr) {
        return 9; 
    }

    return 0; 
}