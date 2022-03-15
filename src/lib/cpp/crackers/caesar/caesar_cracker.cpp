#include "caesar_cracker.hpp"

#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

#include "../ciphers/caesar/caesar_cipher.hpp"
#include "../language_detectors/trie/trie_language_detector.hpp"
namespace crackers
{
caesar_cracker::caesar_cracker(std::shared_ptr<algorithms::caesar_cipher> the_caesar_cipher,
                               std::shared_ptr<detectors::trie_language_detector> the_trie_detector,
                               std::vector<char> the_most_common_letters_in_language)
    : caesar_cipher(the_caesar_cipher),
      trie_detector(the_trie_detector),
      most_common_letters_in_language(the_most_common_letters_in_language)
{
}

char getMostCommonLetter(const std::string& message)
{
    std::map<char, int> frequencyMap;
    auto mostCommonLetter = std::tolower(message[0]);
    frequencyMap.insert(std::pair<char, int>(mostCommonLetter, 1));

    for (std::string::size_type i = 0; i < message.length(); i++)
    {
        if (isspace(message[i]))
        {
            continue;
        }
        auto letter = std::tolower(message[i]);
        auto letterIt = frequencyMap.find(letter);
        if (letterIt != frequencyMap.end())
        {
            letterIt->second += 1;
            if (letterIt->second > frequencyMap.find(mostCommonLetter)->second)
            {
                mostCommonLetter = letter;
            }
        }
        else
        {
            frequencyMap.insert(std::pair<char, int>(letter, 1));
        }
    }
    return mostCommonLetter;
}

std::vector<std::string> caesar_cracker::getPossibleKeys(const std::string& message) const
{
    std::vector<std::string> possibleKeys;
    if (!message.empty())
    {
        auto mostCommonLetterInMessage = getMostCommonLetter(message);
        for (auto common_letter : most_common_letters_in_language)
        {
            possibleKeys.push_back(std::to_string(mostCommonLetterInMessage - std::tolower(common_letter)));
        }
    }
    return possibleKeys;
}

std::string caesar_cracker::crackMessage(const std::string& message) const
{
    if (!message.empty())
    {
        auto possible_keys = this->getPossibleKeys(message);
        for (auto key : possible_keys)
        {
            auto deciphered_message = this->caesar_cipher->decrypt(message, key);

            if (this->trie_detector->languageMatches(deciphered_message))
            {
                return deciphered_message;
            }
        }
    }
    return message;
}

}  // namespace crackers