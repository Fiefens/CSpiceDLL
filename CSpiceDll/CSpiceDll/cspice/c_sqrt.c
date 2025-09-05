#include <math.h>

typedef struct {
    double r;
    double i;
} Complex;

void c_sqrt(Complex* result, const Complex* input) {
    double x = input->r;
    double y = input->i;

    if (x == 0.0 && y == 0.0) {
        result->r = 0.0;
        result->i = 0.0;
        return;
    }

    double magnitude = sqrt(x * x + y * y);
    double t;

    if (x > 0.0) {
        result->r = t = sqrt(0.5 * (magnitude + x));
        result->i = 0.5 * y / t;
    }
    else {
        result->i = t = sqrt(0.5 * (magnitude - x));
        if (y < 0.0) t = -t;
        result->r = 0.5 * y / t;
    }
}
