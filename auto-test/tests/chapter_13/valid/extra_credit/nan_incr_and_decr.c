


int double_isnan(double d); 

int main(void) {
    static double zero = 0.0;
    double nan = 0.0 / zero; 

    if (!double_isnan(++nan)) {
        return 1;
    }

    if (!double_isnan(--nan)) {
        return 2;
    }

    if (!double_isnan(nan++)) {
        return 3;
    }

    if (!double_isnan(nan--)) {
        return 4;
    }

    return 0;
}