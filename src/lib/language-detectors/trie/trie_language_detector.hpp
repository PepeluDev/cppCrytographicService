#pragma once

#include "../language_detector_if.hpp"

#include "trie_tree.hpp"

#include <string>
#include <vector>

namespace detectors {

class trie_language_detector: public language_detector_if
{

private:
    trie_tree* tree;
    double matchingPercentLimit = 60.0;

public:

    trie_language_detector(const std::vector<std::string>& language_dictionary);

    trie_language_detector(const trie_language_detector& t) = delete;
    trie_language_detector(trie_language_detector&& t) = delete;
    trie_language_detector& operator=(const trie_language_detector& t) = delete;
    trie_language_detector& operator=( trie_language_detector&& t) = delete;

    ~trie_language_detector(){
        delete tree;
    }

    bool languageMatches(const std::string& text) const override;

};

}