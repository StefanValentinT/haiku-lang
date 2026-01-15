/* Test that we can propagate copies between char and signed char */

int putchar(int c);  

void print_some_chars(char a, char b, char c, char d) {
    putchar(a);
    putchar(b);
    putchar(c);
    putchar(d);
}

int callee(char c, signed char s) {
    return c == s;
}

int target(char c, signed char s) {
    
    
    
    print_some_chars(67, 66, c, s);

    s = c;  
            

    
    return callee(s, c);
}

int main(void) {
    return target(65, 64);
}