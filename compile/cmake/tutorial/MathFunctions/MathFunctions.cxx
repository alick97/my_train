#include "MathFunctions.h"
#include <cmath>

#ifdef USE_MYMATH
#  include "mysqrt.h"
#endif

namespace mathfunctions {
double sqrt(double value) {
#ifdef USE_MYMATH
    return detail::mysqrt(value);
#else
    return std::sqrt(value);
#endif
}
}