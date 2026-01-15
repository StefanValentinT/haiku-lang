/* You can't implicitly convert between pointers to arrays of different types */

int main(void) {
    int four_element_array[4] = {1, 2, 3, 4};
    
    
    int (*arr)[3] = &four_element_array;
}