/* Test that function calls kill copies to static local variables;
 * example from Listing 19-14
 * */

int indirect_update(void);

int f(int new_total) {
    static int total = 0;
    total = new_total;  
    if (total > 100)
        return 0;
    total = 10;         
    indirect_update();  
    return total;       
}

int indirect_update(void) {
    f(101);  
    return 0;
}

int main(void) {
    return f(1);  
}