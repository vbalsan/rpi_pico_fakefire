
# create generated folder
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/ws2811_library/generated)

# build a normal library
add_library(ws2811_library ${CMAKE_CURRENT_LIST_DIR}/ws2811.c)

# invoke pio_asm to assemble the state machine program
pico_generate_pio_header(ws2811_library ${CMAKE_CURRENT_LIST_DIR}/ws2811.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)


target_link_libraries(ws2811_library PRIVATE pico_stdlib hardware_pio)

# add the `binary` directory so that the generated headers are included in the project
target_include_directories (ws2811_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})