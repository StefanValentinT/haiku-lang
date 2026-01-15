struct s;

extern struct s *ptr;

int main(void) {
  
  return (ptr - ptr) == 0;
}