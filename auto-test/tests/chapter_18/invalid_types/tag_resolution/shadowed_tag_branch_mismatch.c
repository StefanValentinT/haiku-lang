int main(void) {
    struct s {
        int i;
    };
    struct s struct1 = {1};

    {
        struct s {
            int i;
        };
        struct s struct2 = {2};

        
        
        (void)(1 ? struct1 : struct2);
    }
}