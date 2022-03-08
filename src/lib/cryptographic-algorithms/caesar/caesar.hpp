#pragma once

#include "../cryptographic_algorithm_if.hpp"

#include <string>
#include <vector>

namespace algorithms {

class caesar: public cryptographic_algorithm_if
{
public:
    std::string encrypt(std::string message, std::string key) const override;

private:
    bool isCharInAlphabet(char c) const;
    char shiftChar(char c, int number_of_shifts) const;

    const std::string ALPHABET{"abcdefghijklmnopqrstuvwxyz"};
    const int ALPHABET_LEN = 26;
};

}