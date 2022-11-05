# ----------------- SETUP -----------------

cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH "/home/pi/src-code/pico/pico-sdk")

# Pull in SDK (must be before project)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(pico_fakefire)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

# ----------------- PROJECT -----------------

# build the IR receive libraries
add_subdirectory(nec_receive_library)

# Build uart commands libraries
add_subdirectory(DFPlayer_library)

# build the led libraries
add_subdirectory(ws2811_library)

add_executable(pico_fakefire main.c)

# pull in common dependencies and additional pwm hardware support - 
target_link_libraries(pico_fakefire LINK_PUBLIC pico_stdlib hardware_pio ws2811_library nec_receive_library DFPlayer_library)

#usb debug
pico_enable_stdio_usb(pico_fakefire 1)
pico_enable_stdio_uart(pico_fakefire 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(pico_fakefire)

