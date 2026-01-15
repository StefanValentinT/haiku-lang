/* Make sure we can propagate copies into Store instruction */

struct s {
    int a;
    int b;
};

int glob = 0;
int i = 0;
int target(void) {
    int *ptr = &i;
    glob = 30;  

    *ptr = glob;  
                  

    glob = 10;
    return *ptr;
}

int main(void) {
    if (target() != 30) {
        return 1;  
    }
    if (glob != 10) {
        return 2;  
    }
    return 0;  
}