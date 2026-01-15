struct a {
  int x;
  int y;
};

int main(void) {
  struct a my_struct = {1, 2};
  
  return my_struct->x;
}