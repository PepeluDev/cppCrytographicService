#pragma once

#include <functional>
#include <string>
#include <vector>

#include "../cipher_if.hpp"

namespace algorithms
{
class caesar_cipher : public cipher_if
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

}  // namespace algorithms