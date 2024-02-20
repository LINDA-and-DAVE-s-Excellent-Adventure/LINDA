# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(LINDA)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME}
    main.c
    lib/encoding.c
    lib/laser_transmit.c
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_pio
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Configureation for easy ipload
add_compile_definitions(PICO_ON_DEVICE=1)
pico_add_extra_outputs(LINDA)