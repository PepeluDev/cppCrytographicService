#pragma once

#include <string>
#include <vector>

namespace detectors
{
class language_detector_if
{
public:
    virtual ~language_detector_if() = default;
    virtual bool languageMatches(const std::string& text) const = 0;
};
}  // namespace detectors
