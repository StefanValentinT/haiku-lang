/* Test the -> operator.
 * Relatively simple tests without nested accesses or members of aggregate
 * types.
 */

void *calloc(unsigned long nmemb, unsigned long size);

struct four_members {
    double d;
    char c;
    long l;
    char *ptr;
};




double get_double(void) {
    return 2e12;
}

static long l = 34359738378l;



int accept_params(int d_divided, int c_doubled, double l_cast,
                  int dereferenced_ptr, double d, int c, long l, char *ptr) {
    if (d != -1845381177299.0 || c != 127 || l != 58 || *ptr != 100 ||
        d_divided != -922690588 || c_doubled != 254 || l_cast != 58.0 ||
        dereferenced_ptr != 100) {
        return 0;
    }

    return 1;  
}

int test_auto(void) {
    
    
    struct four_members autom;
    struct four_members *autom_ptr = &autom;

    
    autom_ptr->d = (l - get_double()) + (l * 3.5);  
    autom_ptr->c = 127;
    autom_ptr->l = get_double() / l;  

    char chr = 100;
    autom_ptr->ptr = &chr;

    
    if (autom_ptr->d != -1845381177299.0 || autom_ptr->c != 127 ||
        autom_ptr->l != 58 || autom_ptr->ptr != &chr) {
        return 0;
    }

    
    double *d_ptr = &autom_ptr->d;
    char *c_ptr = &autom_ptr->c;
    if (*d_ptr != -1845381177299.0 || *c_ptr != 127) {
        return 0;
    }

    
    if (*autom_ptr->ptr != 100) {
        return 0;
    }

    
    if (!accept_params(autom.d / 2000, autom.c * 2, (double)autom.l, *autom.ptr,
                       autom.d, autom.c, autom.l, autom.ptr)) {
        return 0;
    }

    return 1;
}

int test_static(void) {
    
    
    static struct four_members stat;
    static struct four_members *stat_ptr;
    stat_ptr = &stat;
    static char chr = 100;

    

    
    stat_ptr->d = (l - get_double()) + (l * 3.5);  
    stat_ptr->c = 127;
    stat_ptr->l = get_double() / l;  

    stat_ptr->ptr = &chr;

    
    if (stat_ptr->d != -1845381177299.0 || stat_ptr->c != 127 ||
        stat_ptr->l != 58 || stat_ptr->ptr != &chr) {
        return 0;
    }

    
    double *d_ptr = &stat_ptr->d;
    char *c_ptr = &stat_ptr->c;
    if (*d_ptr != -1845381177299.0 || *c_ptr != 127) {
        return 0;
    }

    
    if (*stat_ptr->ptr != 100) {
        return 0;
    }

    
    if (!accept_params(stat.d / 2000, stat.c * 2, (double)stat.l, *stat.ptr,
                       stat.d, stat.c, stat.l, stat.ptr)) {
        return 0;
    }

    return 1;  
}

int test_exp_result_member(void) {
    
    

    static int flag = 1;

    
    struct four_members s1;
    s1.d = 10.0;
    s1.c = 99;
    s1.l = 9223372036854775807l;
    s1.ptr = 0;

    struct four_members s2;
    s2.d = 12.0;
    s2.c = 98;
    s2.l = -9223372036854775807l;
    s2.ptr = 0;

    struct four_members *s1_ptr = &s1;
    struct four_members *s2_ptr = &s2;

    
    (flag ? s1_ptr : s2_ptr)->c = 127;

    
    if (s1.c != 127) {
        return 0;
    }

    if (s2.c != 98) {  
        return 0;
    }

    
    
    struct four_members *result_ptr = 0;
    
    if ((result_ptr = s2_ptr)->d != 12.0 ||
        
        result_ptr->l != -9223372036854775807l) {
        return 0;
    }

    
    void *void_ptr = calloc(1, sizeof(struct four_members));
    ((struct four_members *)void_ptr)->c = 80;

    
    result_ptr = void_ptr;
    if (result_ptr->c != 80) {
        return 0;
    }

    return 1;  
}

int main(void) {
    
    if (!test_auto()) {
        return 1;
    }

    
    if (!test_static()) {
        return 2;
    }

    if (!test_exp_result_member()) {
        return 3;
    }

    return 0;
}
