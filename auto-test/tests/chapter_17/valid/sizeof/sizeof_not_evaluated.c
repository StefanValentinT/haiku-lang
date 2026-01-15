void exit(int status);
int foo(void) { exit(10); }

int main(void) {
  
  return sizeof(foo());
}