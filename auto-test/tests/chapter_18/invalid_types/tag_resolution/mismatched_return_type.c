struct s {
  int a;
  int b;
};

struct s return_struct(void) {
  
  struct s {
    int a;
    int b;
  };
  struct s result = {1, 2};
  
  
  return result;
}
