add_library(shifters
STATIC
    english/english_shifter.cpp
)

target_include_directories(shifters
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)