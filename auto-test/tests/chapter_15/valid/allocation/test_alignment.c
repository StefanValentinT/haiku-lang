/* Test that we allocate enough space for arrays on the stack
 * and that they're correctly aligned
 * all three arrays are >= 16 bytes so they must be 16-byte aligned
 */

int check_alignment(int *ptr) {
    unsigned long addr = (unsigned long) ptr;
    return (addr % 16 == 0);
}

int main(void)
{
    
    int arr[5] = {0};
    int arr2[7] = {0};
    int arr3[2][2] = {{0}};

    
    if (!check_alignment(arr)) {
        return 1;
    }

    
    for (int i = 0; i < 5; i = i + 1)
        arr[i] = i;

    
    if (!check_alignment(arr2)) {
        return 2;
    }

    
    for (int i = 0; i < 7; i = i + 1)
        if (arr2[i])
            return 3;

    
    for (int i = 0; i < 7; i = i + 1){
        arr2[i] = -i;
    }

    
    if (!check_alignment((int *)arr3)) {
        return 4;
    }

    
    
    for (int i = 0; i < 5; i = i + 1) {
        if (arr[i] != i) {
            return 5;
        }
    }

    for (int i = 0; i < 2; i = i + 1)
        for (int j = 0; j < 2; j = j + 1)
            if (arr3[i][j] != 0)
                return 6;

    return 0;
}