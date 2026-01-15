
struct s {
    int i;
};

union u {
    char arr[3];
    double d;
    struct s my_struct;
};

union u my_union; 

int main(void) {
    union u* u_ptr = &my_union;

    
    
    if ((void*)u_ptr != (void*)&(u_ptr->arr)) {
        return 1; 
    }

    if (!((void*)u_ptr == (void*)&(u_ptr->d))) {
        return 2; 
    }

    if ((void*)&(u_ptr->my_struct) != u_ptr) {
        return 3; 
    }

    
    if (my_union.arr != (char*)&my_union.d) {
        return 4; 
    }

    if (!(&my_union.arr[0] >= (char *) &my_union.my_struct.i)) {
        return 5; 
    }

    if (! ((char *) (&u_ptr->d) <= (char *) &u_ptr->my_struct)) {
        return 6; 
    }

    return 0;
}