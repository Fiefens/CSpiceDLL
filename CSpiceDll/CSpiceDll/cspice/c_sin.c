#include <math.h>

typedef struct {
    double r;
    double i;
} Complex;

void c_sin(Complex* result, const Complex* input) {
    double x = input->r;
    double y = input->i;

    result->r = sin(x) * cosh(y);
    result->i = cos(x) * sinh(y);
}
