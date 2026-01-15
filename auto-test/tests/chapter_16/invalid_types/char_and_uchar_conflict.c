/* char and unsigned char are different types; you can't use them
 * interchangeably when redeclaring the same identifier */
int foo(unsigned char c) {
    return c;
}

int main(void) {
    return foo(0);
}


int foo(char c);