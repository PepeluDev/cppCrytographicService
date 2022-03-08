#pragma once

#include "../cryptographic_algorithm_if.hpp"

#include <functional>
#include <string>
#include <vector>

namespace algorithms {

class caesar: public cryptographic_algorithm_if
{
public:
    std::string encrypt(const std::string& message, const std::string& key) const override;
    std::string decrypt(const std::string& message, const std::string& key) const override;

private:
    bool isCharInAlphabet(char c) const;
    char shiftCharWith(char c, std::function<char(char)> shiftCharLambda) const;
    std::string shiftStringWith(const std::string& message, std::function<char(char)> shiftCharLambda) const;

    const std::string ALPHABET{"abcdefghijklmnopqrstuvwxyz"};
    const int ALPHABET_LEN = 26;
};

}