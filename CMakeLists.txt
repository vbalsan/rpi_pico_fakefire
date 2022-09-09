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

# set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_executable(pico_fakefire)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)

pico_generate_pio_header(pico_fakefire ${CMAKE_CURRENT_LIST_DIR}/ws2811.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(pico_fakefire PRIVATE main.c)

# pull in common dependencies and additional pwm hardware support
target_link_libraries(pico_fakefire PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pico_fakefire)

# create map/bin/hex file etc.
pico_add_extra_outputs(pico_fakefire)

