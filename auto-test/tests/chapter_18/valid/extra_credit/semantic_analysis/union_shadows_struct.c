
struct tag {
    int a;
    int b;
};

struct tag global_struct = {1, 2};

int main(void) {
    
    union tag {
        int x;
        long y;
    };
    union tag local_union = {100};
    if (global_struct.a != 1) {
        return 1;  
    }
    if (local_union.x != 100) {
        return 2;  
    }
    return 0;  
}