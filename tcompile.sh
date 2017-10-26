clear

mkdir -p build
cd build

cmake -DHYPE_PUB_SUB_COMPILE_TESTS:BOOL=ON -G "Unix Makefiles" ../
make

