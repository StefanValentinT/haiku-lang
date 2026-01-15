/* Writing to union member kills previous copies to/from that union */

union u {
    long l;
    int i;
};

int main(void) {
    static union u u1 = {20};
    union u u2 = {3};
    u1 = u2; 
    u2.i = 0; 

    return u1.i;  
}