#include "caesar_cipher.hpp"

#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

namespace algorithms
{
bool caesar_cipher::isCharInAlphabet(char character) const
{
    return ALPHABET[0] <= character && character <= ALPHABET[ALPHABET_LEN - 1];
}

char caesar_cipher::shiftCharWith(char character, std::function<char(char)> shiftCharLambda) const
{
    char lowerChar = std::tolower(character);
    if (!caesar_cipher::isCharInAlphabet(lowerChar))
    {
        std::stringstream exceptionStream;
        exceptionStream << "The " << character << " character is not in the defined alphabet";
        throw std::invalid_argument(exceptionStream.str());
    }
    auto shiftedLowerChar = shiftCharLambda(lowerChar);
    return lowerChar != character ? std::toupper(shiftedLowerChar) : shiftedLowerChar;
}

std::string caesar_cipher::shiftStringWith(const std::string& message, std::function<char(char)> shiftCharLambda) const
{
    std::stringstream sstream;
    for (std::string::size_type i = 0; i < message.length(); i++)
    {
        sstream << (isspace(message[i]) ? message[i] : shiftCharWith(message[i], shiftCharLambda));
    }
    return sstream.str();
}

std::string caesar_cipher::encrypt(const std::string& message, const std::string& key) const
{
    int number_of_shifts = std::stoi(key);
    std::function<char(char)> encryptCharLambda = [this, number_of_shifts](char character)
    {
        auto shiftedPosition = character + number_of_shifts - this->ALPHABET[0];
        shiftedPosition += shiftedPosition < 0 ? this->ALPHABET_LEN : 0;
        return (shiftedPosition % this->ALPHABET_LEN) + this->ALPHABET[0];
    };
    return shiftStringWith(message, encryptCharLambda);
}

std::string caesar_cipher::decrypt(const std::string& message, const std::string& key) const
{
    int number_of_shifts = std::stoi(key);
    std::function<char(char)> decryptCharLambda = [this, number_of_shifts](char character)
    {
        auto shiftedPosition = character - number_of_shifts - this->ALPHABET[0];
        shiftedPosition += shiftedPosition < 0 ? this->ALPHABET_LEN : 0;
        return (shiftedPosition % this->ALPHABET_LEN) + this->ALPHABET[0];
    };
    return shiftStringWith(message, decryptCharLambda);
}

}  // namespace algorithms