#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../cipher_if.hpp"
#include "../shifters/shifter_if.hpp"

namespace algorithms
{
class caesar_cipher : public cipher_if
{
public:
    caesar_cipher();
    caesar_cipher(std::shared_ptr<shifters::shifter_if> shifter);
    std::string encrypt(const std::string& message, const std::string& key) const override;
    std::string decrypt(const std::string& message, const std::string& key) const override;

private:
    std::string shiftString(const std::string& message, int number_of_shifts) const;

    std::shared_ptr<shifters::shifter_if> shifter;
};

}  // namespace algorithms