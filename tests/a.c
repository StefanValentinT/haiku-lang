int f(void);
int f(void);          // redeclaration – OK

int main(void) {
    int f(void);      // redeclaration in inner scope – OK
    return f();
}

int f(void) {         // single definition – OK
    return 3;
}
