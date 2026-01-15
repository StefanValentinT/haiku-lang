/* CopyToOffset does not kill src struct */

struct s {
    int a;
    int b;
    int c;
};

struct s glob = {1, 2, 3};

int main(void) {
    struct s my_struct = glob;  
    my_struct.c = 100;          
    if (my_struct.c != 100 ) {
        return 1; 
    }
    if (my_struct.a != 1) {
        return 2; 
    }
    if (glob.c != 3) {
        return 3; 
    }
    return 0; 
}