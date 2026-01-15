/* Test that we don't propagate copies into AddrOf instructions */
int main(void) {
    long x = 1;
    long y = 2;
    x = y;            
    return &x == &y;  
}