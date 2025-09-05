#include <math.h>

typedef struct {
    double r;
    double i;
} Complex;

void c_exp(Complex* result, const Complex* input) {
    double x = input->r;
    double y = input->i;

    double expx = exp(x);
    result->r = expx * cos(y);
    result->i = expx * sin(y);
}
