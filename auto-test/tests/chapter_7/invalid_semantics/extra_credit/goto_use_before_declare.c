int main(void) {
    int x = 0;
    if (x != 0) {
        return_y:
        return y; 
    }
    int y = 4;
    goto return_y;
}