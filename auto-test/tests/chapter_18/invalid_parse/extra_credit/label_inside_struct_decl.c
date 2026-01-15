/* Labels can't appear inside structure declarations */

struct s {
    int i;
    
    
    foo : int j;
};

int main(void) {
    return 0;
}