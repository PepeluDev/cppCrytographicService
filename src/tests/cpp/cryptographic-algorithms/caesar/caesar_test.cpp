#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "caesar/caesar.hpp"

#include <memory>

using testing::_;

class caesar_test : public ::testing::Test
{
public:
    void SetUp() override {
        caesar = std::make_unique<algorithms::caesar>();
     };

protected:
    std::unique_ptr<algorithms::caesar> caesar;
    const std::string PLAIN_TEXT_MESSAGE = "This is a plain test message";
};

TEST_F(caesar_test, it_should_not_return_an_empty_string)
{
    std::string KEY = "3";

    auto output = caesar->encrypt(PLAIN_TEXT_MESSAGE,KEY);
    ASSERT_FALSE(output.empty());
}

TEST_F(caesar_test, it_should_return_the_same_message_with_a_zero_key)
{
    std::string KEY = "0";

    auto output = caesar->encrypt(PLAIN_TEXT_MESSAGE,KEY);
    ASSERT_EQ(PLAIN_TEXT_MESSAGE,output);
}

TEST_F(caesar_test, it_should_return_the_expected_encrypted_message_with_a_key_in_range)
{
    const auto CIPHERED_MESSAGE = "Wklv lv d sodlq whvw phvvdjh";
    std::string KEY = "3";

    auto output = caesar->encrypt(PLAIN_TEXT_MESSAGE,KEY);
    ASSERT_EQ(CIPHERED_MESSAGE,output);
}

TEST_F(caesar_test, it_should_return_the_expected_encrypted_message_with_a_key_out_of_range)
{
    const auto CIPHERED_MESSAGE = "Xlmw mw e tpemr xiwx qiwweki";
    std::string KEY = "30";

    auto output = caesar->encrypt(PLAIN_TEXT_MESSAGE,KEY);
    ASSERT_EQ(CIPHERED_MESSAGE,output);
}

