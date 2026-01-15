union u {
    int arr[3];
    double d;
};

union u get_union(void) {
    union u result = {{1, 2, 3}, 4.0};
    return result;
}

int main(void) {
    
    
    int *ptr[3] = &get_union().arr;
    return 0;
}