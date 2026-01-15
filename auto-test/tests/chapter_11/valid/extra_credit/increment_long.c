
int main(void) {
    long x = -9223372036854775807l;

    
    if (x++ != -9223372036854775807l) {
        return 1;
    }
    if (x != -9223372036854775806l) {
        return 2;
    }

    
    if (--x != -9223372036854775807l) {
        return 3;
    }
    if (x != -9223372036854775807l) {
        return 4;
    }

    return 0; 
}