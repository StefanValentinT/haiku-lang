struct s1;
struct s2;

struct s1 *get_s1_ptr(void);
struct s2 *get_s2_ptr(void);

int main(void) {
  
  struct s1 *s1_ptr = get_s1_ptr();
  struct s2 *s2_ptr = get_s2_ptr();
  return s1_ptr == s2_ptr;
}