
union u {
    unsigned long l;
    double d;
    char arr[8];
};

static union u my_union = { 18446744073709551615UL };
static union u* union_ptr = 0;

int main(void) {
    union_ptr = &my_union;
    if (my_union.l != 18446744073709551615UL) {
        return 1; 
    }

    for (int i = 0; i < 8; i = i + 1) {
        if (my_union.arr[i] != -1) {
            return 2; 
        }
    }

    union_ptr->d = -1.0;

    if (union_ptr->l != 13830554455654793216ul) {
        return 3; 
    }

    for (int i = 0; i < 6; i = i + 1) {
        
        if (my_union.arr[i]) {
            return 4; 
        }
    }
    if (union_ptr->arr[6] != -16) {
        return 5; 
    }

    if (union_ptr->arr[7] != -65) {
        return 6; 
    }

    return 0; 
}