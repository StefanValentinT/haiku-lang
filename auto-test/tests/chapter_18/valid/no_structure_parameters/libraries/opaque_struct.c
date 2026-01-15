/* Test working with a structure whose type is completed in the library but not
 * the client; this is a common idiom for hiding a library's implementation
 * details */



int strcmp(char *s1, char *s2);
int puts(char *s);
void *malloc(unsigned long size);

struct s {
    int member1;
    double member2;
    char *member3;
};


struct s *create_struct(int i, double d, char *s) {
    struct s *ptr = malloc(sizeof(struct s));
    ptr->member1 = i;
    ptr->member2 = d;
    ptr->member3 = s;
    return ptr;
}


void increment_struct(struct s *ptr) {
    ptr->member1 = ptr->member1 + 1;
    ptr->member2 = ptr->member2 + 1;
    ptr->member3 = ptr->member3;
}


int check_struct(struct s *ptr, int expected_i, double expected_d,
                 char *expected_s) {
    if (ptr->member1 != expected_i) {
        return 0;
    }
    if (ptr->member2 != expected_d) {
        return 0;
    }
    if (strcmp(ptr->member3, expected_s)) {
        return 0;
    }

    return 1;  
}

void print_struct_msg(struct s *ptr) {
    puts(ptr->member3);
}


static struct s internal = {1, 2.0, "static struct"};

struct s *get_internal_struct(void) {
    return &internal;
}



struct s incomplete_var = {3, 4.0, "global struct"};
