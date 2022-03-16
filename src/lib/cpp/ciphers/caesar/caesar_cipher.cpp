#include "caesar_cipher.hpp"

#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "../shifters/english/english_shifter.hpp"
#include "../shifters/shifter_if.hpp"

namespace algorithms
{
caesar_cipher::caesar_cipher()
{
    shifter = std::make_shared<shifters::english_shifter>();
}

caesar_cipher::caesar_cipher(std::shared_ptr<shifters::shifter_if> theShifter) : shifter(theShifter) {}

std::string caesar_cipher::encrypt(const std::string& message, const std::string& key) const
{
    int number_of_shifts = std::stoi(key);
    return shiftString(message, number_of_shifts);
}

std::string caesar_cipher::decrypt(const std::string& message, const std::string& key) const
{
    int number_of_shifts = std::stoi(key);
    number_of_shifts = number_of_shifts * -1;
    return shiftString(message, number_of_shifts);
}

std::string caesar_cipher::shiftString(const std::string& message, int number_of_shifts) const
{
    std::stringstream sstream;
    for (std::string::size_type i = 0; i < message.length(); i++)
    {
        sstream << (isspace(message[i]) ? message[i] : this->shifter->shiftChar(message[i], number_of_shifts));
    }
    return sstream.str();
}

}  // namespace algorithms