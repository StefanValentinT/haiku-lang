struct s;

extern struct s x;
extern struct s y;

int main(void) {
  x = y; 
  return 0;
}