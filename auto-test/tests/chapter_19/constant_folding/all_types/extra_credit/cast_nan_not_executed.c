



static int flse = 0;

int main(void) {
    int retval = 0;
    if (flse) {
        retval = (int) (0.0/0.0);
    }
    return retval;
}