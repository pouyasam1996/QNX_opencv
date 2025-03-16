cmake_minimum_required(VERSION 3.10)
project(QNX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

# Find OpenCV package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} src/include) # Include headers directory

# Add source files
set(SOURCES
        src/src/main.c
        src/src/isp.c
        src/src/display.cpp
        src/src/encoder.c
        src/src/camera_wrapper.cpp
)

# Add executable
add_executable(QNX ${SOURCES})

# Link OpenCV libraries
target_link_libraries(QNX ${OpenCV_LIBS})