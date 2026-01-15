/* A variable is live if it's used later on one path but not others.
 * Loosely based on figure 19-10
 * */

int f(int arg, int flag) {
    int x = arg * 2;  
    if (flag)
        return x;
    return 0;
}

int main(void) {
    if (f(20, 1) != 40) {
        return 1;  
    }
    if (f(3, 0) != 0) {
        return 2;  
    }
    return 0;  
}