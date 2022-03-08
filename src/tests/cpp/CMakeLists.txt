add_executable( unit-test "")

target_link_libraries( unit-test
PRIVATE
        cryptographic-algorithms
        ssl
        crypto
        dl
        gtest
        gmock
        gtest_main
        pthread
)

add_subdirectory(cryptographic-algorithms)
