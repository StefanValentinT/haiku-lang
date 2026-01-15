

union u1 {int a;};
union u2 {int a;};

int main(void){
    union u1 x = {10};
    union u2 y = {11};
    x = y; 
    return 0;
}