/* Test that we remove useless labels */
int target(void) {
    
    
    do {
    } while (0);

    return 99;
}

int main(void) {
    return target();
}