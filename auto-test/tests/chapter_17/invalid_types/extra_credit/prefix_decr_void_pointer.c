
void *malloc(unsigned long size);

int main(void) {
    void *buff = malloc(100);
    --buff;
    return 0;
}