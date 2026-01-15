

int main(void) {

    static char c = 100;
    char c2 = 100;
    c += c2; 
    if (c != -56) {
        return 1; 
    }

    static unsigned char uc = 200;
    c2 = -100;
    uc /= c2; 
    if (uc != 254) {
        return 2; 
    }

    uc -= 250.0; 
    if (uc != 4) {
         return 3;  
    }

    static signed char sc = 70;
    sc = -sc;
    sc *= c;
    if (sc != 80) {
        return 4; 
    }

    if ((sc %= c) != 24) {
        return 5;
    }

    return 0;
}