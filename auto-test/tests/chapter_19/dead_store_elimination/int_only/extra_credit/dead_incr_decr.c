/* Test that we delete ++/-- with dead variables */


static int glob;

int target(void) {
    
    int a = glob;
    int b = glob;
    int c = glob;
    int d = glob;
    
    a++;
    b--;
    ++c;
    --d;
    return 10;
}

int main(void) {
    return target();
}