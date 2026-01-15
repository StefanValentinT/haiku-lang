int foo(int **x) {
    return x[0][0];
}

int main(void) {
    int arr[1] = {10};
    return foo(&arr); 
}