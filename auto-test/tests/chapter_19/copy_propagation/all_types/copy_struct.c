/* Test that we can propagate copies of aggregate values */
struct s {
    int x;
    int y;
};

int callee(struct s a, struct s b) {
    if (a.x != 3) {
        return 1; 
    }
    if (a.y != 4) {
        return 2; 
    }
    if (b.x != 3) {
        return 3; 
    }
    if (b.y != 4) {
        return 4; 
    }
    return 0; 
}

int target(void) {
    struct s s1 = {1, 2};
    struct s s2 = {3, 4};
    s1 = s2;  

    
    
    
    
    return callee(s1, s2);
}

int main(void) {
    return target();
}