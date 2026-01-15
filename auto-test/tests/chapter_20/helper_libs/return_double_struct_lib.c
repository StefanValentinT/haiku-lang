
struct s {
    double d1;
    double d2;
};


struct s return_struct(void);

int target(void) {
    struct s retval = return_struct();
    if (retval.d1 != 0.0) {
        printf("Expected retval.d1 to have value 0.0, actual value was %f\n",
               retval.d1);
        exit(-1);
    }
    if (retval.d2 != 200.0) {
        printf("Expected retval.d2 to have value 200.0, actual value was %f\n",
               retval.d2);
        exit(-1);
    }
    return 0;
}
