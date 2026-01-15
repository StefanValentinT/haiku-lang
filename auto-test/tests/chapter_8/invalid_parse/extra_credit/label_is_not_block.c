int main(void) {
    int a = 0;
    int b = 0;
    
    
    do
    do_body:
        a = a + 1;
        b = b - 1;
    while (a < 10)
        ;
    return 0;
}