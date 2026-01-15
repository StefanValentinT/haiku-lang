/* If a variable is only used as the controlling condition for an empty branch
 * we can eliminate the branch, then eliminate any updates to that variable,
 * because they'll all be dead stores
 * */




int flag = 1;

int target(void) {
    int x = 2;
    if (flag) {
        x = 20;  
                 
                 
    }

    if (x)
        ;

    
    return 10;
}

int main(void) {
    return target();
}