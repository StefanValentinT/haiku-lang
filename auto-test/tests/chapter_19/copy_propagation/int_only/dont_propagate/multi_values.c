/* Test for meet operator: if different copies to a variable
 * reach the ends of a block's predecessors, no copies to that variable
 * reach that block
 * */

int multi_path(int flag) {
    int x = 3;  
    if (flag)
        x = 4;  

    
    
    
    return x;
}

int main(void) {
    if (multi_path(1) != 4) {
        return 1;
    }

    if (multi_path(0) != 3) {
        return 2;
    }

    return 0;  
}