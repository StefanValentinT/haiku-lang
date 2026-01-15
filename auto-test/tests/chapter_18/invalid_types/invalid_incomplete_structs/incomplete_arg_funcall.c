struct s;

void f(struct s param);

extern struct s extern_var;

int main(void) {
  
  f(extern_var);
}