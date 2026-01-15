
int main(void) {
    static int i = 65;
    switch (i) {
        case 100l:
            return 1;  
        case 'A':
            return 0;  
        case 'B':
            return 2;  
        case 2000u:
            return 3;  
        default:
            return -1;  
    }
}