#include "MathFunctions.h"

double mysqrt(double x) {
    double val = x;
    double last;
    do {
        last = val;
        val = (val + x/val) / 2;
    } while(abs(val - last) > E);
    
    return val;
}
