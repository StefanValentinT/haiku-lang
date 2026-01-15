void *malloc(unsigned long size);

struct a {
  int x;
  int y;
};

int main(void) {
  struct a *ptr = malloc(sizeof(struct a));
  ptr.x = 10; 
}