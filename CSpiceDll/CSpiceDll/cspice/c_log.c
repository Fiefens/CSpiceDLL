#include <math.h>

typedef struct {
    double r;
    double i;
} Complex;

void c_log(Complex* result, const Complex* input) {
    double x = input->r;
    double y = input->i;

    result->r = log(sqrt(x * x + y * y));  // magnitude
    result->i = atan2(y, x);              // angle
}
