#include <math.h>

typedef struct {
    double r;
    double i;
} Complex;

void c_cos(Complex* result, const Complex* input) {
    double x = input->r;
    double y = input->i;

    result->r = cos(x) * cosh(y);
    result->i = -sin(x) * sinh(y);
}
