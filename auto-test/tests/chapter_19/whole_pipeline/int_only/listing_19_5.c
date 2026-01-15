/* Test case that produces TACKY similar to Listing 19-5;
 * this should be optimized to a single "Return 9" instruction */




int flag = 1;

int target(void) {
    int x = 4;
    int z;
    if (4 - x) {
        x = 3;
    }
    if (!flag) {
        z = 10;
    }
    z = x + 5;
    return z;
}

int main(void) {
    return target();
}