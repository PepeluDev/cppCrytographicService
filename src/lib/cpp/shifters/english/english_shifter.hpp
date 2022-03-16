#pragma once

#include <functional>
#include <string>

#include "../shifter_if.hpp"

namespace shifters
{
class english_shifter : public shifter_if
{
public:
    char shiftChar(char c, int number_of_shifts) const;

private:
    char getShiftedChar(char character, int number_of_shifts) const;
    bool isCharInAlphabet(char c) const;

    const std::string ALPHABET{"abcdefghijklmnopqrstuvwxyz"};
    const int ALPHABET_LEN = 26;
};

}  // namespace shifters