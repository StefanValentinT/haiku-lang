/* Helper functions defined in tests/chapter_20/helper_libs/util.c */

/* The check_* functions return 0 on success,
 * print and exit with code -1 on failure.
 */

int check_one_int(int actual, int expected);


int check_5_ints(int a, int b, int c, int d, int e, int start);


int check_12_ints(int a, int b, int c, int d, int e, int f, int g, int h, int i,
                  int j, int k, int l, int start);


int id(int x);
