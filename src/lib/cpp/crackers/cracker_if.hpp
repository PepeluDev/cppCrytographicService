#pragma once

#include <string>
#include <vector>

namespace crackers
{
class cracker_if
{
public:
    virtual ~cracker_if() = default;
    virtual std::string crackMessage(const std::string& message) const = 0;
    virtual std::vector<std::string> getPossibleKeys(const std::string& message) const = 0;
};
}  // namespace crackers
