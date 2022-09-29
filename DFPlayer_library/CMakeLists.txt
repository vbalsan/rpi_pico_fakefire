
# build a normal library
add_library(DFPlayer_library ${CMAKE_CURRENT_LIST_DIR}/DFPlayerCommands.c)


target_link_libraries(DFPlayer_library PRIVATE pico_stdlib hardware_uart )

# add the `binary` directory so that the generated headers are included in the project
target_include_directories (DFPlayer_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})