union u {
    int x;
};

union u return_union(void){
    
    union u {
        int x;
    };

    union u result = {10};

    
    return result;
}
