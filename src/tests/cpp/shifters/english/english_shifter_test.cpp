#include "english/english_shifter.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cctype>
#include <memory>
#include <sstream>

using testing::_;

class english_shifter_test : public ::testing::Test
{
public:
    void SetUp() override { englishShifter = std::make_unique<shifters::english_shifter>(); };

protected:
    std::unique_ptr<shifters::english_shifter> englishShifter;

    const std::string PLAIN_TEXT_MESSAGE = "This is ba plain test message";
    const std::string SHIFTED_MESSAGE = "Wklv lv ed sodlq whvw phvvdjh";
    const int DEFAULT_NUMBER_OF_SHIFTS = 3;
    const char DEFAULT_TESTING_CHAR = 'a';
    const char DEFAULT_TESTING_CHAR_SHIFTED_WITH_DEFAULT_NUMBER_OF_SHIFTS = 'd';
    const char DEFAULT_TESTING_CHAR_SHIFTED_BACKWARDS_WITH_DEFAULT_NUMBER_OF_SHIFTS = 'x';
    const char DEFAULT_TESTING_OUT_OF_THE_ALPHABET_CHAR = '*';

    bool isCharInEnglishAlphabet(char character) const { return 'a' <= character && character <= 'z'; }
};

TEST_F(english_shifter_test, it_should_return_the_same_char_if_the_number_of_shifts_is_equal_to_zero)
{
    auto output = englishShifter->shiftChar(DEFAULT_TESTING_CHAR, 0);
    ASSERT_EQ(DEFAULT_TESTING_CHAR, output);
}

TEST_F(english_shifter_test, it_should_not_modify_the_letter_case_when_shifting)
{
    auto lowerCaseShifted = englishShifter->shiftChar(DEFAULT_TESTING_CHAR, DEFAULT_NUMBER_OF_SHIFTS);
    auto upperCaseShifted = englishShifter->shiftChar(toupper(DEFAULT_TESTING_CHAR), DEFAULT_NUMBER_OF_SHIFTS);

    EXPECT_TRUE(islower(lowerCaseShifted));
    EXPECT_TRUE(isupper(upperCaseShifted));
}

TEST_F(english_shifter_test, it_should_return_the_expected_char_using_the_expected_number_of_shifts)
{
    auto output = englishShifter->shiftChar(DEFAULT_TESTING_CHAR, DEFAULT_NUMBER_OF_SHIFTS);
    ASSERT_EQ(DEFAULT_TESTING_CHAR_SHIFTED_WITH_DEFAULT_NUMBER_OF_SHIFTS, output);
}

TEST_F(english_shifter_test, it_should_shift_backwards_if_the_number_of_shifts_is_negative)
{
    auto output = englishShifter->shiftChar(DEFAULT_TESTING_CHAR_SHIFTED_WITH_DEFAULT_NUMBER_OF_SHIFTS,
                                            -1 * DEFAULT_NUMBER_OF_SHIFTS);
    ASSERT_EQ(DEFAULT_TESTING_CHAR, output);
}

TEST_F(english_shifter_test,
       it_should_do_the_shift_from_the_opposite_side_of_the_alphabet_if_the_number_of_shifts_is_out_of_range)
{
    auto outOfRangeShiftedUnderTheAlphabet =
        englishShifter->shiftChar(DEFAULT_TESTING_CHAR, -1 * DEFAULT_NUMBER_OF_SHIFTS);
    auto outOfRangeShiftedOverTheAlphabet = englishShifter->shiftChar(
        DEFAULT_TESTING_CHAR_SHIFTED_BACKWARDS_WITH_DEFAULT_NUMBER_OF_SHIFTS, DEFAULT_NUMBER_OF_SHIFTS);

    EXPECT_EQ(DEFAULT_TESTING_CHAR_SHIFTED_BACKWARDS_WITH_DEFAULT_NUMBER_OF_SHIFTS, outOfRangeShiftedUnderTheAlphabet);
    EXPECT_EQ(DEFAULT_TESTING_CHAR, outOfRangeShiftedOverTheAlphabet);
}

TEST_F(english_shifter_test, it_should_throw_if_a_character_out_of_the_english_alphabet_is_tried_to_be_shifted)
{
    ASSERT_FALSE(isCharInEnglishAlphabet(DEFAULT_TESTING_OUT_OF_THE_ALPHABET_CHAR));
    try
    {
        englishShifter->shiftChar(DEFAULT_TESTING_OUT_OF_THE_ALPHABET_CHAR, DEFAULT_NUMBER_OF_SHIFTS);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const& err)
    {
        EXPECT_EQ(err.what(), std::string("The \'*\' character is not in the defined alphabet"));
    }
    catch (...)
    {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST_F(english_shifter_test, it_should_perform_the_expected_shifting_operations)
{
    std::stringstream strstream;
    for (std::size_t i = 0; i < PLAIN_TEXT_MESSAGE.length(); i++)
    {
        strstream << (isspace(PLAIN_TEXT_MESSAGE[i])
                          ? PLAIN_TEXT_MESSAGE[i]
                          : englishShifter->shiftChar(PLAIN_TEXT_MESSAGE[i], DEFAULT_NUMBER_OF_SHIFTS));
    }
    ASSERT_EQ(SHIFTED_MESSAGE, strstream.str());
}

TEST_F(english_shifter_test, it_should_perform_the_expected_backward_shifting_operations)
{
    std::stringstream strstream;
    for (std::size_t i = 0; i < SHIFTED_MESSAGE.length(); i++)
    {
        strstream << (isspace(SHIFTED_MESSAGE[i])
                          ? SHIFTED_MESSAGE[i]
                          : englishShifter->shiftChar(SHIFTED_MESSAGE[i], -1 * DEFAULT_NUMBER_OF_SHIFTS));
    }
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, strstream.str());
}

TEST_F(english_shifter_test,
       it_should_return_valid_english_letters_event_if_the_number_of_shifts_is_larger_than_the_alphabet)
{
    for (std::size_t i = 0; i < PLAIN_TEXT_MESSAGE.length(); i++)
    {
        if (isspace(PLAIN_TEXT_MESSAGE[i]))
        {
            continue;
        }
        EXPECT_TRUE(isCharInEnglishAlphabet(tolower(englishShifter->shiftChar(PLAIN_TEXT_MESSAGE[i], 30))));
    }
}

TEST_F(english_shifter_test,
       it_should_return_valid_english_letters_event_if_the_number_of_negative_shifts_is_larger_than_the_alphabet)
{
    for (std::size_t i = 0; i < PLAIN_TEXT_MESSAGE.length(); i++)
    {
        if (isspace(PLAIN_TEXT_MESSAGE[i]))
        {
            continue;
        }
        EXPECT_TRUE(isCharInEnglishAlphabet(tolower(englishShifter->shiftChar(PLAIN_TEXT_MESSAGE[i], -30))));
    }
}
