

union u { long l; };

int main(void){
    union u x = {1};
    x == x; 
    return 0;
}