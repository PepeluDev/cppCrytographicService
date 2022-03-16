#pragma once

#include <string>

namespace algorithms
{
class cipher_if
{
public:
    virtual ~cipher_if() = default;
    virtual std::string encrypt(const std::string& message, const std::string& key) const = 0;
    virtual std::string decrypt(const std::string& message, const std::string& key) const = 0;
};
}  // namespace algorithms
