struct one {
  int x;
  int y;
};

struct two {
  int a;
  int b;
};

struct one return_struct(void) {
    struct two retval = {1, 2};
    return retval; 
}

int main(void) {
    return return_struct().x;
}