

union u1 {
    int a;
};


int main(void){
    union u1 var = {10};
    (union u1) var; 
    return 0;
}