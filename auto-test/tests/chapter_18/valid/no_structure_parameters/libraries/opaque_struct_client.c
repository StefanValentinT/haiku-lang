/* Test working with a structure whose type is completed in the library but not
 * the client; this is a common idiom for hiding a library's implementation
 * details */

struct s;  


struct s *create_struct(int i, double d, char *s);
void increment_struct(struct s *src_ptr);

int check_struct(struct s *ptr, int expected_i, double expected_d,
                 char *expected_s);
void print_struct_msg(struct s *ptr);
struct s *get_internal_struct(void);


extern struct s incomplete_var;

int main(void) {
    struct s *new_struct = create_struct(101, 102.0, "new struct");

    struct s *internal_struct = get_internal_struct();

    
    print_struct_msg(new_struct);
    print_struct_msg(internal_struct);
    print_struct_msg(&incomplete_var);

    
    increment_struct(new_struct);
    increment_struct(&incomplete_var);

    
    if (!check_struct(new_struct, 102, 103.0, "new struct")) {
        return 1;
    }

    if (!check_struct(&incomplete_var, 4, 5.0, "global struct")) {
        return 2;
    }

    return 0;  
}