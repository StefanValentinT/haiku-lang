struct s {
  int a;
};

int main(void) {
  struct s x = {1};
  
  if (x)
    return 1;
  return 0;
}