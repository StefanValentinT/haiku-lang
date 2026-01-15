
union inner {
    int y;
    long z;
};

union u {
    int x;
    union inner i;
};

union u return_union(void){
    union u result = {1};
    return result;
}

int main(void) {
    
    return_union().i.y = 1;
    return 0;
}