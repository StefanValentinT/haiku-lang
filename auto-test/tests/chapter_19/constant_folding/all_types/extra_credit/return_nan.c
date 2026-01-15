/* Test case where we return NaN after constant folding */

int double_isnan(double d); 

double target(void) {
    return 0.0 / 0.0;
}

int main(void) {
    double nan = target();
    if (double_isnan(nan)) {
        return 0; 
    }

    return 1; 
}