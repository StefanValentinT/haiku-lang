/* Test that the Briggs test also applies to hard registers.
 * In other words, we'll coalesce a pseudoregister and hard register that pass
 * the Briggs test even if they don't pass the George test. We inspect the
 * assembly for the target function to validate that it contains no spills and
 * no mov instructions whose source and destination are both general-purpose
 * registers (except mov %rsp, %rbp and mov %rbp, %rsp in the prologue and
 * epilogue).
 * NOTE: it's theoretically possible but very unlikely that every variable
 * could end up in the right register by accident and the test could pass
 * even if we don't perform register coalescing.
 * */


int flag = 1;

int target(void) {
    int coalesce_into_eax = 0;
    
    if (flag) {  
        
        
        coalesce_into_eax = id(10);
    }

    
    
    
    int high_degree = 2 * coalesce_into_eax;  

    
    
    if (coalesce_into_eax != 10) {
        return -1;
    }

    
    
    
    
    
    
    
    int twelve = 32 - high_degree;
    int eleven = 23 - twelve;
    int ten = 21 - eleven;
    int nine = 19 - ten;
    int eight = 17 - nine;
    int seven = 15 - eight;
    int six = 13 - seven;
    
    
    int five = 11 - six;
    int four = 24 - high_degree;
    int three = 23 - high_degree;
    int two = 22 - high_degree;
    int one = 21 - high_degree;
    
    
    
    check_5_ints(one, two, three, four, five, 1);

    return 0;  
}