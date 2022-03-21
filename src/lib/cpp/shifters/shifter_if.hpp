#pragma once

namespace shifters
{
class shifter_if
{
public:
    virtual ~shifter_if() = default;
    virtual char shiftChar(char c, int number_of_shifts) const = 0;
    virtual char shiftCharWithChar(char c, char shifter_index_character, bool backwards) const = 0;
};
}  // namespace shifters
