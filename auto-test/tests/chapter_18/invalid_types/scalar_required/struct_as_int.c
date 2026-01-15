struct s {
  int a;
};

int main(void) {
  struct s x = {1};
  
  (void)~x;
  return 0;
}