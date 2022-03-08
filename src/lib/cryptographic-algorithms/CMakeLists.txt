add_library(cryptographic-algorithms
STATIC
    caesar/caesar.cpp
)

target_include_directories(cryptographic-algorithms
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)