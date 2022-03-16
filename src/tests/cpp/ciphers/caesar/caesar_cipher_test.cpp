#include "caesar/caesar_cipher.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

using testing::_;

class caesar_test : public ::testing::Test
{
public:
    void SetUp() override { caesarCipher = std::make_unique<algorithms::caesar_cipher>(); };

protected:
    std::unique_ptr<algorithms::caesar_cipher> caesarCipher;
    const std::string PLAIN_TEXT_MESSAGE = "This is a plain test message";
    const std::string CIPHERED_MESSAGE = "Wklv lv d sodlq whvw phvvdjh";
    const std::string DEFAULT_KEY = "3";
};

TEST_F(caesar_test, it_should_not_return_an_empty_string_when_encrypt)
{
    auto output = caesarCipher->encrypt(PLAIN_TEXT_MESSAGE, DEFAULT_KEY);
    ASSERT_FALSE(output.empty());
}

TEST_F(caesar_test, it_should_return_the_same_message_with_a_zero_key_when_encrypt)
{
    std::string KEY = "0";

    auto output = caesarCipher->encrypt(PLAIN_TEXT_MESSAGE, KEY);
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, output);
}

TEST_F(caesar_test, it_should_return_the_expected_encrypted_message_with_a_key_in_range_when_encrypt)
{
    auto output = caesarCipher->encrypt(PLAIN_TEXT_MESSAGE, DEFAULT_KEY);
    ASSERT_EQ(CIPHERED_MESSAGE, output);
}

TEST_F(caesar_test, it_should_return_the_expected_encrypted_message_with_a_key_out_of_range_when_encrypt)
{
    const auto CIPHERED_MESSAGE = "Xlmw mw e tpemr xiwx qiwweki";
    std::string KEY = "30";

    auto output = caesarCipher->encrypt(PLAIN_TEXT_MESSAGE, KEY);
    ASSERT_EQ(CIPHERED_MESSAGE, output);
}

TEST_F(caesar_test, it_should_return_the_expected_encrypted_message_with_a_negative_key_out_of_range_when_encrypt)
{
    const auto CIPHERED_MESSAGE = "Znoy oy g vrgot zkyz skyygmk";
    std::string KEY = "-20";

    auto output = caesarCipher->encrypt(PLAIN_TEXT_MESSAGE, KEY);
    ASSERT_EQ(CIPHERED_MESSAGE, output);
}

TEST_F(caesar_test, it_should_not_return_an_empty_string_when_decrypt)
{
    auto output = caesarCipher->decrypt(CIPHERED_MESSAGE, DEFAULT_KEY);
    ASSERT_FALSE(output.empty());
}

TEST_F(caesar_test, it_should_return_the_same_message_with_a_zero_key_when_decrypt)
{
    std::string KEY = "0";

    auto output = caesarCipher->decrypt(CIPHERED_MESSAGE, KEY);
    ASSERT_EQ(CIPHERED_MESSAGE, output);
}

TEST_F(caesar_test, it_should_return_the_expected_decrypted_message_with_a_key_in_range_when_decrypt)
{
    auto output = caesarCipher->decrypt(CIPHERED_MESSAGE, DEFAULT_KEY);
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, output);
}

TEST_F(caesar_test, it_should_return_the_expected_encrypted_message_with_a_key_out_of_range_when_decrypt)
{
    const auto CIPHERED_MESSAGE = "Xlmw mw e tpemr xiwx qiwweki";
    std::string KEY = "30";

    auto output = caesarCipher->decrypt(CIPHERED_MESSAGE, KEY);
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, output);
}

TEST_F(caesar_test, it_should_return_the_expected_encrypted_message_with_a_negative_key_out_of_range_when_decrypt)
{
    const auto CIPHERED_MESSAGE = "Znoy oy g vrgot zkyz skyygmk";
    std::string KEY = "-20";

    auto output = caesarCipher->decrypt(CIPHERED_MESSAGE, KEY);
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, output);
}