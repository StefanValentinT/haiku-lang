/* A pointer to a string can only be assigned to a pointer to an array
 * with the correct length. */

int main(void) {
    
    
    char(*string_pointer)[10] = &"x";
    return 0;
}