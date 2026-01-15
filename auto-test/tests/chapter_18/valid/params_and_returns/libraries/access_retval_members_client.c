/* Test for accessing the members in a return value of structure type */

int main(void) {
    
    if (return_small_struct().y != 102) {
        return 1;
    }

    
    if (return_nested_struct().d != 2.0 || return_nested_struct().s.x != 10 ||
        return_nested_struct().s.y != 11) {
        return 3;
    }

    
    if (return_nested_struct().ptr->x != 12 ||
        return_nested_struct().ptr->y != 13) {
        return 4;
    }

    
    return_nested_struct().ptr->x = 70;
    return_nested_struct().ptr->y = 71;

    
    if (return_nested_struct().ptr->x != 70 ||
        return_nested_struct().ptr->y != 71) {
        return 5;
    }

    return 0;  
}