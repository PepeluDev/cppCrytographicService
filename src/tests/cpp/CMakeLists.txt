add_executable( unit-test "")

target_link_libraries( unit-test
PRIVATE
        shifters
        language_detectors
        ciphers
        crackers
        ssl
        crypto
        dl
        gtest
        gmock
        gtest_main
        pthread
)

add_subdirectory(shifters)
add_subdirectory(ciphers)
add_subdirectory(language_detectors)
add_subdirectory(crackers)
