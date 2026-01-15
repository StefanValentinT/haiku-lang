/* We can recognize that one store to a variable is a dead store,
 * but another store to that variable at a different point in the program
 * is not.
 * */
int callee(int arg) {
    return arg * 2;
}

int target(int arg, int flag) {
    int x = arg + 1;   
    if (flag) {
        
        
        
        x = arg - 1;
    }
    int y = callee(x); 
    x = 100;  
    return y;
}

int main(void) {
    if (target(4, 0) != 10) {
        return 1; 
    }
    if (target(3, 1) != 4) {
        return 2; 
    }
    return 0; 
}