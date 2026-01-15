/* Test that we can call all the memory management functions */

void *malloc(unsigned long size);
void *realloc(void *ptr, unsigned long size);
void *calloc(unsigned long nmemb, unsigned long size);
void *aligned_alloc(unsigned long alignment, unsigned long size);
void free(void *ptr);

int main(void) {
    
    char *char_buffer = malloc(50);
    for (int i = 0; i < 50; i = i + 1) {
        char_buffer[i] = i;
    }

    
    char *char_buffer2 = realloc(char_buffer, 100);
    
    
    char_buffer2[75] = 11;

    
    for (int i = 0; i < 50; i = i + 1) {
        if ( char_buffer2[i] != i) {
            return 1;
        }
    }

    
    if (char_buffer2[75] != 11) {
        return 2;
    }

    free(char_buffer2);

    
    double *double_buffer = calloc(10, sizeof(double));
    for (int i = 0; i < 10; i = i + 1) {
        if (double_buffer[i]) {
            return 3;
        }
    }
    free(double_buffer);

    
    char_buffer = aligned_alloc(256, 256);
    
    if ((unsigned long) char_buffer % 256) {
        return 4;
    }
    free(char_buffer);
    return 0;
}