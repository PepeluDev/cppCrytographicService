add_library(crackers
STATIC
    caesar/caesar_cracker.cpp
)

target_include_directories(crackers
PRIVATE
    ${CMAKE_SOURCE_DIR}/src/lib/cpp/ciphers
    ${CMAKE_SOURCE_DIR}/src/lib/cpp/language_detectors
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)