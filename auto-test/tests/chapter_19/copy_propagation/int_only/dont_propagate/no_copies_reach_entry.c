/* Make sure we track that the set of reaching copies from ENTRY is empty */
int target(int a, int flag) {
    if (flag) {
        
        
        
        return a;
    }

    a = 10;  
    return a;
}

int main(void) {
    return target(4, 1);
}