#include "TutorialConfig.h"
#ifdef USE_MYMATH
#  include "MathFunctions.h"
#else
#  include <cmath>
#endif



#include <iostream>

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        // report version.
        std::cout << "Version: " << Tutorial_VERSION_MAJOR << "."
                  << Tutorial_VERSION_MINOR << std::endl;
        return 1;
    }
    const double inputValue = std::stod(argv[1]);
#ifdef USE_MYMATH
    const double outputValue = mysqrt(inputValue);
#else
    const double outputValue = sqrt(inputValue);
#endif
    std::cout << argv[1] << " is " << outputValue << std::endl;
    return 0;
}