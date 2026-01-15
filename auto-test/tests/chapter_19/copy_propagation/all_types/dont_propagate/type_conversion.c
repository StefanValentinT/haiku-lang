/* Test that we don't propagate copies between values of different types,
 * since that will lead to incorrect assembly generation (e.g. for comparisons
 * and division). (If we had separate TACKY operators for signed vs unsigned
 * comparisons/division/remainder operations instead of inferring signedness
 * from TACKY operand types, it would be save to propagate these copies.)
 */
int target(int i) {
    unsigned int j = i;
    return (j / 100);  
                       
                       
}

int main(void) {
    return target(-200) == 42949670;
}