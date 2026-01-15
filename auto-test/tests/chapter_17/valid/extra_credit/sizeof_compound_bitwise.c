



int main(void) {
    static signed char sc = 10;
    unsigned int u = 10000u;
    long l = -99999;

    if (sizeof(sc &= l) != 1) {
        return 1;  
    }

    if (sizeof(l |= u) != 8) {
        return 2;  
    }

    if (sizeof(u ^= l) != 4) {
        return 3;  
    }
    if (sizeof(l >>= sc) != 8) {
        return 4;
    }
    if (sizeof(sc <<= sc) != 1) {
        return 5;
    }

    
    if (sc != 10) {
        return 6;  
    }
    if (u != 10000u) {
        return 7;  
    }
    if (l != -99999) {
        return 8;  
    }

    return 0;
}