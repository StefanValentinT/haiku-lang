/* Test that we correctly get the size of a range of expressions */


void *malloc(unsigned long size);
void free(void *ptr);

int main(void) {
    

    double d;

    if (sizeof d != 8) {
        return 2;
    }

    unsigned char c;

    if (sizeof c != 1) {
        return 3;
    }

    void *buffer = malloc(100);

    
    if (sizeof(buffer) != 8) {
        return 4;
    }

    free(buffer);

    

    
    
    if (sizeof ((int)d) != 4) {
        return 5;
    }

    
    if (sizeof (d ? c : 10l) != 8) {
        return 6;
    }

    

    if (sizeof (c = 10.0) != 1) {
        return 7;
    }

    return 0;
}