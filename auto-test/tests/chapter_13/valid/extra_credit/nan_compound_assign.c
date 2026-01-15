


int double_isnan(double d); 

int main(void) {
    static double zero = 0.0;
    double nan = 0.0 / zero; 

    if (!double_isnan(nan += 99.2)) {
        return 1;
    }

    if (!double_isnan(nan -= nan)) {
        return 2;
    }

    if (!double_isnan(nan *= 4.0)) {
        return 3;
    }

    if (!double_isnan(nan /= 0.0)) {
        return 4;
    }

    return 0;
}