/* Test that we treat character constants like integers */


double d = '\\'; 

int main(void) {

    if (d != 92.0) {
        return 1;
    }

    
    
    unsigned long array['\n'] = {1, 2, 'a', '\b', 3, 4, 5, '!', '%', '~'};

    if (array[2] != 97) {
        return 2;
    }

    if (array[3] != 8) {
        return 3;
    }

    if (array[7] != 33) {
        return 4;
    }

    if (array[8] != 37) {
        return 5;
    }

    if (array[9] != 126) {
        return 6;
    }

    
    
    unsigned long (*array_ptr)[10] = &array;

    if (array_ptr[0][9] != '~') {
        return 7;
    }

    
    int i = array['\a']; 
    if (i != 33) {
        return 8;
    }

    
    double d = 10 % '\a' + 4.0 * '_' - ~'@'; 

    if (d != 448.0) {
        return 9;
    }
    return 0;
}