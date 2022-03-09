#include "trie_language_detector.hpp"

#include <cstring>
#include <string>
#include <vector>

namespace detectors
{
trie_language_detector::trie_language_detector(const std::vector<std::string>& language_dictionary)
    : tree(new trie_tree())
{
    this->tree->addWords(language_dictionary);
}

void splitText(std::string const& str, const char* delimiter, std::vector<std::string>& out)
{
    char* token = strtok(const_cast<char*>(str.c_str()), delimiter);
    while (token != nullptr)
    {
        out.push_back(std::string(token));
        token = strtok(nullptr, delimiter);
    }
}

bool trie_language_detector::languageMatches(const std::string& text) const
{
    if (text.empty())
    {
        return false;
    }
    std::vector<std::string> splittedText{};
    splitText(text, " ", splittedText);
    int numberOfWordsInTrie = 0;
    for (auto word : splittedText)
    {
        if (tree->containsWord(word))
        {
            numberOfWordsInTrie++;
        }
    }

    return (static_cast<double>(numberOfWordsInTrie) * 100 / static_cast<double>(splittedText.size())) >=
           this->matchingPercentLimit;
}
}  // namespace detectors