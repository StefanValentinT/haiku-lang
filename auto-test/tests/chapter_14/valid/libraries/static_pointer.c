


static long *long_ptr;

long *get_pointer(void) {
    return long_ptr;
}

int set_pointer(long *new_ptr) {
    long_ptr = new_ptr;
    return 0;
}