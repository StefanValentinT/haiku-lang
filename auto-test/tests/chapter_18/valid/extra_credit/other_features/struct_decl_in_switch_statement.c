

struct s {
    int a;
    int b;
};

int main(void) {
    struct s my_struct = {1, 2};
    int result = 0;
    switch (my_struct.a) {
        
        
        struct s {
            double x;
            double y;
            double z;
        };
        
        struct s my_struct;
        case 1:
            my_struct.x = 20.0;
            my_struct.y = 30.0;
            result = my_struct.x + my_struct.y;
            break;
        case 2:
            my_struct.x = 11.;
            my_struct.y = 12.;
            result = my_struct.x + my_struct.y;
            break;
        default:
            my_struct.x = 0.;
            my_struct.y = 0.;
            result = my_struct.x + my_struct.y;
    }
    return result; 
}