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
    char shiftChar(char c, int number_of_shifts) const;
    char shiftCharWith(char c, int number_of_shifts,std::function<char(char,int)> shiftCharLambda) const;
    std::string shiftStringWith(const std::string& message, const std::string& key, std::function<char(char,int)> shiftCharLambda) const;

    const std::string ALPHABET{"abcdefghijklmnopqrstuvwxyz"};
    const int ALPHABET_LEN = 26;
};

}