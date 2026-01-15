/* Test that we can use strings literals as function arguments/return values */


unsigned long strlen(char *s);

char *return_string(void) {
    
    
    return "I'm a string!";
}

int pass_string_args(char *s1, char *s2) {
    
    if (s1 == 0 || s2 == 0) {
        return 0;
    }

    if (strlen(s1) != 45) {
        return 0;
    }

    if (s1[41] != 'd' || s1[42] != 'o' || s1[43] != 'g') {
        return 0;
    }

    
    if (s2[0]) {
        return 0;
    }

    return 1;  
}

int main(void) {
    char *ptr = 0;
    
    ptr = return_string();
    if (!ptr)
        return 1;

    if (ptr[0] != 'I' || ptr[1] != '\'' || ptr[13]) {
        return 2;
    }

    
    if (!pass_string_args("The quick brown fox jumped over the lazy dog.",
                          "")) {
        return 3;
    }

    return 0;

    char *ptr2;
    ptr2 = 1 ? ptr + 2 : ptr + 4;
    return *ptr2 == 'm';
}