


int puts(char *s);

int main(void) {
    
    char flat_arr[4] = "abc";
    puts(flat_arr);

    
    flat_arr[2] = 'x';
    puts(flat_arr);

    
    char nested_array[2][6] = {"Hello", "World"};
    puts(nested_array[0]);
    puts(nested_array[1]);

    nested_array[0][0] = 'J';
    puts(nested_array[0]);

    return 0;
}