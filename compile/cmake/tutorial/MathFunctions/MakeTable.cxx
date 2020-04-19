#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " filepath" << std::endl;
    }
    const char *filePath = argv[1];
    std::ofstream myfile;
    myfile.open(filePath, std::ios::out | std::ios::trunc);
    if (myfile.is_open()) {
        myfile << "#ifndef __TABLE_H__" << std::endl
               << "#define __TABLE_H__" << std::endl
               << "double sqrtTable[] = {" << std::endl;
        for (int i = 0; i < 10; ++i) {
            double result = sqrt(static_cast<double>(i));
            if (i == 0) {
                myfile << "    " << result;
            } else {
                myfile << ", " << result;
            }
        }
        myfile << std::endl << "};" << std::endl
               << "#endif" << std::endl;
    } else {
        std::cout << "Unable to open file" << std::endl;
        myfile.close();
        return 1;
    }

    myfile.close();
    return 0;
}
