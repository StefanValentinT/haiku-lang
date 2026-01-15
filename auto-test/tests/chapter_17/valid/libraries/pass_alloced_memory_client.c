/* Test passing pointers to allocated memory between translation units */


void *get_100_zeroed_bytes(void);
void fill_100_bytes(void *pointer, int byte);
void free_bytes(void *ptr);

int main(void) {

    void *mem = get_100_zeroed_bytes();
    
    for (int i = 0; i < 100; i = i + 1) {
        if (((char *) mem + i)[0]) {
            return 1;
        }
    }

    
    fill_100_bytes(mem, 99);

    
    for (int i = 0; i < 100; i = i + 1) {
        if (((char *) mem + i)[0] != 99) {
            return 2;
        }
    }

    
    free_bytes(mem);

    return 0;
}