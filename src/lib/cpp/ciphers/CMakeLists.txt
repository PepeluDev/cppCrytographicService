add_library(ciphers
STATIC
    caesar/caesar_cipher.cpp
)

target_include_directories(ciphers
PRIVATE
    ${CMAKE_SOURCE_DIR}/src/lib/cpp/shifters
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ciphers
PRIVATE
-static
    # Keep the list of files sorted from down to top.
    shifters
)
