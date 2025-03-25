# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.22.1)

# Add a library to be built
add_library( # Specifies the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/native_lib.cpp
)