/* Function calls kill copies to variables with static storage duration */
int x;

int update_x(void) {
    x = 4;
    return 0;
}

int target(void) {
    x = 3;       
    update_x();  
    return x;    
}

int main(void) {
    
    if (target() != 4) {
        return 1;
    }

    if (x != 4) {
        return 2;
    }

    return 0;  
}