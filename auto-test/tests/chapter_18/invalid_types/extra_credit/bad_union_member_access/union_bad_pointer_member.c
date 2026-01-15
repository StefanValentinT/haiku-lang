void *malloc(unsigned long size);

union a {
  int x;
  int y;
};

union b {
  int m;
  int n;
};

int main(void) {
  union a *ptr = malloc(sizeof(union a));
  ptr->m = 10; 
  return 0;
}
