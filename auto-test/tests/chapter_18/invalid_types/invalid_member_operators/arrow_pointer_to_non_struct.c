struct s {
    long l;
};

int main(void) {
    double d = 0.0;
    double* ptr = &d;
    return ptr->l;  
}