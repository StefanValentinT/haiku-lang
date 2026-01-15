/* Test initialization of nested static structs, including:
 * - partial initialization
 * - arrays of structs, structs containing arrays
 * - implicit conversion of scalar elements, array decay of string literals
 */








struct outer all_zeros;


struct outer partial = {
    100l,
    {10, {10}},  
    "Hello!"};   

struct outer full = {
    18014398509481979l,
    {1000, "ok",
     4292870144u},  
    "Another message",
    2e12};

struct outer converted = {
    10.5,  
    {
        2147483650u,  
        {
            15.6,             
            17592186044419l,  
            2147483777u       
        },
        1152921506754330624ul  
    },
    0ul,                   
    9223372036854776833ul  
};

struct outer struct_array[3] = {{1, {2, "ab", 3}, 0, 5},
                                {6, {7, "cd", 8}, "Message", 9}};

int main(void) {
    if (!test_uninitialized()) {
        return 1;
    }

    if (!test_partially_initialized()) {
        return 2;
    }

    if (!test_fully_intialized()) {
        return 3;
    }

    if (!test_implicit_conversions()) {
        return 4;
    }

    if (!test_array_of_structs()) {
        return 5;
    }

    return 0;  
}