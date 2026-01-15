/* NaN controlling expressions are treated as true */

int target(void) {
    double nan = 0.0 / 0.0;
    if (nan) {
        return 0; 
    }
    return 1; 
}

int main(void) {
    return target();
}