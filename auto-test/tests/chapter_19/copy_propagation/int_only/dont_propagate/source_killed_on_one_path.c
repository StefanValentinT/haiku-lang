/* If a copy is generated on all paths to a block,
 * and its source is updated on one path,
 * it doesn't reach that block
 * */

int putchar(int c);  

int f(int src, int flag) {
    int x = src;  
    if (flag) {
        src = 65;  
    }
    putchar(src);  
    return x;      
}

int main(void) {
    
    
    
    if (f(68, 0) != 68) {
        return 1;
    }

    
    
    
    if (f(70, 1) != 70) {
        return 2;
    }

    return 0;  
}