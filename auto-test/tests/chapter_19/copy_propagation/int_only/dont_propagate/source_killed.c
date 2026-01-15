/* Basic test that updating the source of a copy kills that copy */

int x = 10;

int main(void) {
    int y = x;      
    x = 4;          
    if (y != 10) {  
        return 1;
    }
    if (x != 4) {
        return 2;
    }
    return 0;  
}