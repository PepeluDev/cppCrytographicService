#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../ciphers/caesar/caesar_cipher.hpp"
#include "../cracker_if.hpp"
#include "../language_detectors/trie/trie_language_detector.hpp"

namespace crackers
{
class caesar_cracker : public cracker_if
{
public:
    caesar_cracker(std::shared_ptr<algorithms::caesar_cipher> the_caesar_cipher,
                   std::shared_ptr<detectors::trie_language_detector> the_trie_detector,
                   std::vector<char> the_most_common_letters_in_language);

    std::string crackMessage(const std::string& message) const override;
    std::vector<std::string> getPossibleKeys(const std::string& message) const override;

private:
    std::shared_ptr<algorithms::caesar_cipher> caesar_cipher;
    std::shared_ptr<detectors::trie_language_detector> trie_detector;
    std::vector<char> most_common_letters_in_language;
};

}  // namespace crackers