/* Declare the same global array multiple times w/ equivalent declarators */


long int(arr)[4] = {1, 2, 3, 4};

int long arr[4ul];


int (*ptr_to_arr)[3][6l];

int((*(ptr_to_arr))[3l])[6u] = 0;


int *array_of_pointers[3] = {0, 0, 0};


int test_arr(void) {
    for (int i = 0; i < 4; i = i + 1) {
        if (arr[i] != i + 1) {
            return 1;
        }
    }
    return 0; 
}

int test_ptr_to_arr(void) {
    
    if (ptr_to_arr) {
        return 2;
    }

    static int nested_arr[3][6];
    ptr_to_arr = &nested_arr;
    ptr_to_arr[0][2][4] = 100;
    if (nested_arr[2][4] != 100) {
        return 3;
    }
    return 0; 
}

int test_array_of_pointers(int *ptr) {

    extern int *((array_of_pointers)[3]); 

    
    
    for (int i = 0; i < 3; i = i + 1) {
        if (array_of_pointers[i])
            return 4;
        array_of_pointers[i] = ptr;
    }

    
    array_of_pointers[2][0] = 11;

    if (*ptr != 11) {
        return 5;
    }

    for (int i = 0; i < 3; i = i + 1) {
        if (array_of_pointers[i][0] != 11) {
            return 6;
        }
    }
    return 0;

}

int main(void)
{
    
    int check = test_arr();
    if (check) {
        return check;
    }

    
    check = test_ptr_to_arr();
    if (check) {
        return check;
    }

    
    int x = 0;
    check = test_array_of_pointers(&x);
    if (check) {
        return check;
    }

    return 0;
}