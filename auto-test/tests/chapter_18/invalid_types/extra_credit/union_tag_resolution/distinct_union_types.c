int foo(void) {
    union s {
        int a;
        long b;
    };
    union s result = {1};
    return result.a;
}

int main(void) {
    
    
    union s;
    
    union s blah = {foo()};
    return blah.a;
}