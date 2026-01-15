
int main(void) {
    
    static int (*array_of_pointers[3])[4] = {0, 0, 0};
    int array1[4] = {100, 101, 102, 103};
    int nested_array[2][4] = {
        {200, 201, 202, 203},
        {300, 301, 302, 303}
    };
    array_of_pointers[0] = &array1;
    array_of_pointers[1] = &nested_array[0];
    array_of_pointers[2] = &nested_array[1];

    array_of_pointers[0] += 1; 
    if (array_of_pointers[0][-1][3] != 103) {
        return 1; 
    }

    
    array_of_pointers[1] += 1;
    array_of_pointers[2] -= 1;
    if (array_of_pointers[1][0][3] != 303) {
        return 2; 
    }
    if (array_of_pointers[2][0][3] != 203) {
        return 3; 
    }

    return 0;
}