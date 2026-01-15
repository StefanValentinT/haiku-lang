struct pair {
  int a;
  int b;
};

struct pair x = {1, 2};
struct outer {
    double d;
    struct pair inner;
};


struct outer y = {1.0, x};