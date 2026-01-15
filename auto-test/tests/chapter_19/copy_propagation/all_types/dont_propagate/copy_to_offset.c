/* Test that CopyToOffset kills its destination */
struct s {
    int x;
    int y;
};

int main(void) {
    static struct s s1 = {1, 2};
    struct s s2 = {3, 4};
    s1 = s2;   
    s2.x = 5;  

    return s1.x;  
}