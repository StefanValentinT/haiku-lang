int main(void) {
    long l = -34359738368l; 
    int i = -10;
    /* We should convert i to a long, then subtract from l */
    l -= i;
    if (l != -34359738358l) {
        return 1;
    }
    return 0;
}