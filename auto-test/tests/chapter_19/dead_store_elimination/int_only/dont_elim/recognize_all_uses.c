/* Make sure we recognize all the different ways a variable
 * can be used/generated (in Unary, Binary, JumpIfZero, etc.) */

int test_jz(int flag, int arg) {
    if (flag) {
        arg = 0;  
                  
                  
    }
    return arg ? 1 : 2;
}

int test_jnz(int flag, int arg) {
    if (flag) {
        arg = 0;
    }
    return arg || 0;
}

int test_binary(int flag, int arg1, int arg2) {
    if (flag == 0) {
        arg1 = 4;  
                   
                   
    } else if (flag == 1) {
        arg2 = 3;  
    }
    return arg1 * arg2;  
}

int test_unary(int flag, int arg) {
    if (flag) {
        arg = 5;  
                  
                  
    }
    return -arg;  
}

int f(int arg) {
    return arg + 1;
}

int test_funcall(int flag, int arg) {
    if (flag) {
        arg = 7;  
                  
                  
    }
    return f(arg);
}

int main(void) {
    if (test_jz(1, 1) != 2) {  
        return 1; 
    }
    if (test_jz(0, 1) != 1) {  
        return 2; 
    }
    if (test_jnz(1, 1) != 0) {  
        return 3; 
    }
    if (test_jnz(0, 1) != 1) {  
        return 4; 
    }
    if (test_binary(0, 8, 9) != 36) {  
        return 5; 
    }
    if (test_binary(1, 8, 9) != 24) {  
        return 6; 
    }
    if (test_binary(2, 8, 9) != 72) {  
        return 7; 
    }
    if (test_unary(0, 8) != -8) {
        return 8;  
    }
    if (test_unary(1, 8) != -5) {
        return 9;  
    }
    if (test_funcall(1, 5) != 8) {  
        return 10; 
    }
    if (test_funcall(0, 9) != 10) {  
        return 11; 
    }
    return 0;
}