/* Test that we don't coalesce a pseudo into a hardreg if they fail the George
 * and Briggs tests - specifically, when they're connected by a mov of the form
 * movl %pseudoreg, %hardreg. (See george_dont_coalesce.c for an equivalent
 * test where the hardreg is the first instruction.) Coalescing registers
 * that fail the George test here would force us to spill, so we inspect the
 * assembly for target to make sure there are no spills.
 * */


int glob = 1;

int update_glob(void) {
    glob = 0;
    return 0;
}

int target(void) {
    
    
    
    
    

    
    int a = glob * 2;  
    int b = glob * 3;  
    int c = glob * 4;  
    int d = glob * 5;  
    int e = glob * 6;  
    
    update_glob();
    
    int f = a + d;      
    int g = b * 3 - 1;  
    int h = c + d;      
    int i = c + e;      
    int j = d * 2 + 1;  
    int k = e * 2;      
    
    int l = a + b + c + d + e;  
    int m = 3 * f;              
    int n = g * 3 - 2;          
    int o = h * 2 + 5;          
    int p = i * 2 + 4;          

    
    glob = glob + f + g + h + i + j + k; 

    
    
    check_5_ints(l, m, n, o, p, 20);

    
    check_one_int(glob, 57);
    return 0;
}
