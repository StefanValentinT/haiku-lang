int globvar = 0;

int callee(int arg) {
    globvar = arg;
    return 0;
}

int target(int flag) {
    int arg = 10;
    switch (flag) {
        case 1:
            arg = 20;
            break;
        case 2:
            
            
            callee(arg);
            break;
        default:
            globvar = -1;
    }
    return 0;
}

int main(void) {
    target(2);
    if (globvar == 10) {
        return 0; 
    }

    return 1; 
}