cmake_minimum_required(VERSION 2.8)

# Set project
project(sp_test C)

# CMake won't find packages under "/usr/local" by default.
# Add the parent path of the config ('cmake') folder to deal with it.
set(CMAKE_PREFIX_PATH "/usr/local/lib")

# Find libserialport package
find_package(libserialport REQUIRED)

# Include directories
include_directories(${LIBSERIALPORT_INCLUDE_DIRS})

# Set dependencies
set(PROJECT_DEPS ${LIBSERIALPORT_LIBRARIES})
if(Win32)
    set(PROJECT_DEPS ${PROJECT_DEPS} setupapi)
endif()

# Compile test program
add_executable(test_open_device
    ${CMAKE_CURRENT_SOURCE_DIR}/test_open_device.c
    )
set_target_properties(test_open_device PROPERTIES
    OUTPUT_NAME test_open_device)

# Link libraries
target_link_libraries(test_open_device ${PROJECT_DEPS})
