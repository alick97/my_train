mkdir -p debug release
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
cd ..

cd release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cd ..

cpack --config MultiCPackConfig.cmake
