/* Test initialization of nested structs with automatic storage duration,
 * including:
 * - partial initialization
 * - using mix of compound and single initializers to initialize nested structs
 * - arrays of structs, structs containing arrays
 * */





int test_full_initialization(void) {
    struct outer full = {-200,
                         {-171l, {-56, -54, -53}, 40.5},
                         "Important message!",
                         -22,
                         {1, 2}};

    return validate_full_initialization(&full);
}


int test_partial_initialization(void) {
    struct outer partial = {1000,
                            {
                                1,
                                
                            },
                            "Partial"};  

    return validate_partial_initialization(&partial);
}



int test_mixed_initialization(void) {
    struct inner inner1 = {10};
    struct inner inner2 = {20, {21}, 22u};
    static int flag = 0;

    struct outer mixed = {
        200,
        flag ? inner1 : inner2,  
        "mixed",
        10.0,
        {99,
         100}  
    };

    return validate_mixed_initialization(&mixed);
}


int test_array_of_structs(void) {
    struct outer s0 = {1, {2, {3, 4, 5}, 6}, "7", 8.0, {9, 10}};

    struct inner in1 = {102, {103, 104, 105}, 106};
    struct pair pair1 = {109, 110};
    struct pair pair2 = {209};

    struct outer s3 = {301};

    struct outer struct_array[4] = {
        
        s0,
        {101, in1, "107", 108.0, pair1},
        
        
        {201,
         
         {202, {203}},
         "207",
         208.0,
         pair2},
        
        
        s3};

    return validate_array_of_structs(struct_array);
}

int main(void) {
    if (!test_full_initialization()) {
        return 1;
    }

    if (!test_partial_initialization()) {
        return 2;
    }

    if (!test_mixed_initialization()) {
        return 3;
    }

    if (!test_array_of_structs()) {
        return 4;
    }

    return 0;  
}