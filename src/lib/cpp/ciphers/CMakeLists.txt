add_library(ciphers
STATIC
    caesar/caesar_cipher.cpp
)

target_include_directories(ciphers
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)