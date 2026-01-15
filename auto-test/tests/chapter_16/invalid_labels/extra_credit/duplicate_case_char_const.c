

int main(void) {
    static int i = 120;
    switch (i) {
        case 'x':  
            return 1;
        case 120:  
            return 2;
        default:
            return 3;
    }
}