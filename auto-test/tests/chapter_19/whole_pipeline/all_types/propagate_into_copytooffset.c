/* Make sure we can propagate copies into CopyToOffset instruction */

struct s {
    int a;
    int b;
};

int glob = 0;

int target(void) {
    struct s my_struct = {1, 2};

    glob = 30;  

    my_struct.b = glob;  
                         

    glob =
        10;  
    return my_struct.b;
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