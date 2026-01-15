

int main(void) {
    int x = 10;
    if ((x ^ 'A') != 75) {
        return 1;  
    }

    static char c = 132;  
    if (('!' | c) != -91) {
        return 2;  
    }

    static unsigned long ul = 9259400834947493926ul;
    if ((ul & '~') != 38) {
        return 3;  
    }

    if ((ul << ' ') != 4611738958194278400ul) {
        return 4;  
    }

    if (('{' >> 3) != 15) {
        return 5;  
    }

    return 0;
}