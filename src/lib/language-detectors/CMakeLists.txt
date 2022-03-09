add_library(language-detectors
STATIC
    trie/trie_tree.cpp
    trie/trie_language_detector.cpp
)

target_include_directories(language-detectors
INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)