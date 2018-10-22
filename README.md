# Project

This project is a demo of a publish-subscribe system based on the HypeSDK, for the Linux platform.

# Compilation

The project can be compiled using the provided CMakeLists file. You can compile the project using the following commands:

```bash
mkdir -p build && cd build
cmake -G "Unix Makefiles" ../
make
```

If you also want to compile the unit tests you can use the following commands (This requires the CUnit test framework to be installed):

```bash
mkdir -p build && cd build
cmake -G "Unix Makefiles" -DHYPE_PUB_SUB_COMPILE_TESTS ../
make
```