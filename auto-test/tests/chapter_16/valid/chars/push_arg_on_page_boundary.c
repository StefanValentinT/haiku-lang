







extern char zed; 
int foo(int a, int b, int c, int d, int e, int f, char g) {
    return g + 1;
}

int main(void) {
    return foo(0, 0, 0, 0, 0, 0, zed);
}