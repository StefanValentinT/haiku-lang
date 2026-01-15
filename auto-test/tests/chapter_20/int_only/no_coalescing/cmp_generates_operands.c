/* Make sure we recognize that cmp uses both of its operands.
 * Don't inspect assembly; just validate the program's behavior.
 * Note: this only works as intended after we've implemented register
 * coalescing.
 * */

int glob = 10;
int glob2 = 20;

int main(void) {
    int a = glob + 5; 
    int b = glob2 - 5; 

    
    
    
    glob = a + glob; 
    glob2 = b + glob2; 

    if (a != b) {
        return -1;
    }
    
    check_one_int(glob, 25);
    check_one_int(glob2, 35);
    return 0;
}