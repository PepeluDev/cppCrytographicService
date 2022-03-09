#pragma once

#include <string>

namespace algorithms
{
class cryptographic_algorithm_if
{
public:
    virtual ~cryptographic_algorithm_if() = default;
    virtual std::string encrypt(const std::string& message, const std::string& key) const = 0;
    virtual std::string decrypt(const std::string& message, const std::string& key) const = 0;
};
}  // namespace algorithms
