#include <iostream>
#include "mysqrt.h"
#include "Table.h"


namespace mathfunctions {
namespace detail {
// a hack square root calculation using simple operations
double mysqrt(double x) {
    double result = x;
    double last;

    if (x <= 0) {
        return 0;
    }

    // use the table to help find an initial value.
    if (x >= 1 && x < 10) {
        std::cout << "Use the table to help find an initial value " << std::endl;
        result = sqrtTable[static_cast<int>(x)];
    }
    
    // do ten iterations.
    for (int i = 0; i < 10; ++i) {
        if (result <= 0) {
            result = 0.1;
        }
        // f(t) = t * t
        // f'(t) = 2t
        // f(result) - f(result0) = f'(result0)(result - result0)
        //                        = 2 * result0 * (result - result0)
        // delta = f(t) - f(result0) ---> x - (result0 * result0)
        // result = result0 + delta / 2 / result0
        double delta = x - (result * result);
        result = result + 0.5 * delta / result;
    }
    std::cout << "Computing sqrt of " << x << " to be " << result << std::endl;

    return result;
}
}
}