struct inner {
  int a;
  int b;
};

struct outer {
  struct inner x;
};

int main(void) {
  struct outer x = {{1, 2}};
  
  
  struct outer y = {1, x};
  return 0;
}