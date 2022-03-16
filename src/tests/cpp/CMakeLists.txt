add_executable( unit-test "")

target_link_libraries( unit-test
PRIVATE
        language_detectors
        ciphers
        ssl
        crypto
        dl
        gtest
        gmock
        gtest_main
        pthread
)

add_subdirectory(ciphers)
add_subdirectory(language_detectors)
