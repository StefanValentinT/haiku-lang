

int target(void) {
    int x = 5;

    int y = x++;
    int z = ++x;


    int a = 0;
    int b = --a;
    int c = a--;

    if (x == 7 && y == 5 && z == 7 && a == -2 && b == -1 && c == -1 )  {
        return 0; 
    }

    return 1; 
}

int main(void) {
    return target();
}