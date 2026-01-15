

double fmax(double x, double y); 

double get_max(double a, double b, double c, double d,
               double e, double f, double g, double h,
               
               double i, double j, double k)
{

    double max = fmax(
        fmax(
            fmax(
                fmax(a, b),
                fmax(c, d)),
            fmax(
                fmax(e, f),
                fmax(g, h))),
        fmax(i, fmax(j, k)));
    return max;
}
