#include "MathFunctions.h"

double mysqrt(double x) {
    double val = x;
    double last;

#if defined(HAVE_LOG) && defined(HAVE_EXP)
    val = exp(log(x) * 0.5);
    std::cout << "Computing sqrt of " << x << " to be " << val
              << " using log and exp" << std::endl;
#else
    do {
        last = val;
        val = (val + x/val) / 2;
    } while(abs(val - last) > E);
#endif

    return val;
}
