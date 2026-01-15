
void f(void) {
    return;
}

int main(void) {
    switch(f()) {
        default: return 0;
    }
}