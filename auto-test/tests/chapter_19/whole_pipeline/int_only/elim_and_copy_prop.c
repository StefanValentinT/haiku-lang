/* If we can replace every use of a variabe with its value,
 * we can delete the copy to that variable
 * */
int target(void) {
    int x = 10;  
    return x;    
}

int main(void) {
    return target();
}