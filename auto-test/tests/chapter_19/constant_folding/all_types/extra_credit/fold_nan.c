/* Test that we can constant fold an operation that results in NaN;
 * the whole_pipeline folder includes a test that we can constant fold
 * operations _using_ NaN.
 */

int double_isnan(double d); 

double target_nan(void){
    return 0./0.;
}

int main(void) {
    if (!double_isnan(target_nan())) {
        return 1;
    }

    return 0;
}