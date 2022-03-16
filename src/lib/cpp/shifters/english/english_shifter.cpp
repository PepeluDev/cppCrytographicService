#include "english_shifter.hpp"

#include <cctype>
#include <sstream>
#include <string>

namespace shifters
{
bool english_shifter::isCharInAlphabet(char character) const
{
    return ALPHABET[0] <= character && character <= ALPHABET[ALPHABET_LEN - 1];
}

char english_shifter::shiftChar(char character, int number_of_shifts) const
{
    char lowerChar = std::tolower(character);
    if (!this->isCharInAlphabet(lowerChar))
    {
        std::stringstream exceptionStream;
        exceptionStream << "The \'" << character << "\' character is not in the defined alphabet";
        throw std::invalid_argument(exceptionStream.str());
    }
    auto shiftedLowerChar = getShiftedChar(lowerChar, number_of_shifts);
    return lowerChar != character ? std::toupper(shiftedLowerChar) : shiftedLowerChar;
}

char english_shifter::getShiftedChar(char character, int number_of_shifts) const
{
    auto shiftedPosition = character + number_of_shifts - this->ALPHABET[0];
    shiftedPosition += shiftedPosition < 0 ? this->ALPHABET_LEN : 0;
    shiftedPosition %= this->ALPHABET_LEN;
    shiftedPosition += shiftedPosition < 0 ? this->ALPHABET[ALPHABET_LEN - 1] : this->ALPHABET[0];
    return shiftedPosition;
}

}  // namespace shifters