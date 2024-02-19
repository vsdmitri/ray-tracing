mkdir build
cp CMakeLists.txt build
cp -r src build
cp -r includes build
cp -r glm build
cd build
cmake .
make


