


union no_padding {
    char c;
    unsigned char uc;
    signed char arr[11];
};




union with_padding {
    signed char arr[10];
    unsigned int ui;
};






union contains_array {
    union with_padding arr1[2];
    union no_padding arr[3];
};



union double_and_int {
    int i;
    double d;
};


union contains_structs {
    struct wonky x; 
    struct eight_bytes y; 
};

int main(void) {
    if (sizeof(union no_padding) != 11) {
        return 1; 
    }

    if (sizeof(union with_padding) != 12) {
        return 2; 
    }

    if (sizeof(union contains_array) != 36) {
        return 3; 
    }

    if (sizeof(union double_and_int) != 8) {
        return 4; 
    }

    if (sizeof(union contains_structs) != 20) {
        return 5; 
    }


    
    union no_padding x = { 1 };
    union contains_array y = { {{{-1, 2}} }};
    union contains_structs* get_union_ptr(void);

    if (sizeof x != 11) {
        return 6; 
    }

    if (sizeof y.arr1 != 24) { 
        return 7; 
    }

    if (sizeof * get_union_ptr() != 20) {
        return 8; 
    }


    return 0; 
}

union contains_structs* get_union_ptr(void) {
    
    return 0;
}