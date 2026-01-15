struct s {
  int a;
};
int foo(int a) { return a; }

int main(void) {
  struct s x = {1};
  
  return foo(x);
}