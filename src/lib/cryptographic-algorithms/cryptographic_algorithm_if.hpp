#pragma once

#include <string>

namespace algorithms
{

class cryptographic_algorithm_if
{
public:
    virtual ~cryptographic_algorithm_if() = default;
    virtual std::string encrypt(std::string message, std::string key) const = 0;
};
}  // namespace algorithms
