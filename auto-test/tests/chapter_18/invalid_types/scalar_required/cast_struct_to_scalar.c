struct s {
  int a;
};

int main(void) {
  struct s x = {1};
  
  int y = (int)x;
  return y;
}