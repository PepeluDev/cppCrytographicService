#include "vigenere_cipher.hpp"

#include <cctype>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

#include "../shifters/english/english_shifter.hpp"
#include "../shifters/shifter_if.hpp"

namespace algorithms
{
vigenere_cipher::vigenere_cipher()
{
    shifter = std::make_shared<shifters::english_shifter>();
}

vigenere_cipher::vigenere_cipher(std::shared_ptr<shifters::shifter_if> theShifter) : shifter(theShifter) {}

std::string vigenere_cipher::encrypt(const std::string& message, const std::string& key) const
{
    return (message.empty() || key.empty()) ? message : shiftString(message, key);
}

std::string vigenere_cipher::decrypt(const std::string& message, const std::string& key) const
{
    return (message.empty() || key.empty()) ? message : shiftString(message, key, true);
}

std::string vigenere_cipher::shiftString(const std::string& message, const std::string& key, bool backwards) const
{
    int keySize = key.length();
    int keyIndex = 0;

    std::stringstream sstream;
    for (std::string::size_type i = 0; i < message.length(); i++)
    {
        if (isspace(message[i]))
        {
            sstream << message[i];
            continue;
        }
        sstream << this->shifter->shiftCharWithChar(message[i], std::tolower(key[keyIndex % keySize]), backwards);
        keyIndex++;
    }
    return sstream.str();
}

}  // namespace algorithms