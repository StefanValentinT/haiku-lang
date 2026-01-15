struct s;

extern struct s *ptr;

int main(void) {
  
  return ptr + 0 == ptr;
}