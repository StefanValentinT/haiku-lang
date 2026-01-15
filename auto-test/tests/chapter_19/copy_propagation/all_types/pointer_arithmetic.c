/* Test that we propagate copies into AddPtr instructions */
int target(void) {
    int nested[3][23] = {{0, 1}, {2}};

    
    
    
    
    
    
    
    
    
    
    return nested[1][0];
}

int main(void) {
    return target();
}