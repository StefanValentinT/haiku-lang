/* Dead store elimination should never eliminate Store instructions
 * */
void f(int *ptr) {
    *ptr = 4;  
    return;
}

int main(void) {
    int x = 0;
    f(&x);
    return x;
}