#include "caesar/caesar_cipher.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

// A fake shifter implementation is needed, or a mock
// These tests shouldn't be based on a concrete shifter.
#include "english/english_shifter.hpp"

using testing::_;

class caesar_cipher_test : public ::testing::Test
{
public:
    void SetUp() override
    {
        caesarCipher = std::make_unique<algorithms::caesar_cipher>(std::make_shared<shifters::english_shifter>());
    };

protected:
    std::unique_ptr<algorithms::caesar_cipher> caesarCipher;
    const std::string PLAIN_TEXT_MESSAGE = "This is a plain test message";
    const std::string CIPHERED_MESSAGE = "Wklv lv d sodlq whvw phvvdjh";
    const std::string DEFAULT_KEY = "3";
};

TEST_F(caesar_cipher_test, it_should_not_return_an_empty_string_when_encrypt)
{
    auto output = caesarCipher->encrypt(PLAIN_TEXT_MESSAGE, DEFAULT_KEY);
    ASSERT_FALSE(output.empty());
}

TEST_F(caesar_cipher_test, it_should_not_return_an_empty_string_when_decrypt)
{
    auto output = caesarCipher->decrypt(CIPHERED_MESSAGE, DEFAULT_KEY);
    ASSERT_FALSE(output.empty());
}

TEST_F(caesar_cipher_test, it_should_return_the_same_message_with_a_zero_key_when_decrypt)
{
    std::string KEY = "0";

    auto output = caesarCipher->decrypt(CIPHERED_MESSAGE, KEY);
    ASSERT_EQ(CIPHERED_MESSAGE, output);
}

TEST_F(caesar_cipher_test, it_should_return_the_same_message_with_a_zero_key_when_encrypt)
{
    std::string KEY = "0";

    auto output = caesarCipher->encrypt(PLAIN_TEXT_MESSAGE, KEY);
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, output);
}

TEST_F(caesar_cipher_test, it_should_return_the_expected_encrypted_message_with_a_key_in_range_when_encrypt)
{
    auto output = caesarCipher->encrypt(PLAIN_TEXT_MESSAGE, DEFAULT_KEY);
    ASSERT_EQ(CIPHERED_MESSAGE, output);
}

TEST_F(caesar_cipher_test, it_should_return_the_expected_encrypted_message_with_a_key_bigger_than_a)
{
    auto output = caesarCipher->encrypt(PLAIN_TEXT_MESSAGE, "102");
    ASSERT_EQ("Rfgq gq y njygl rcqr kcqqyec", output);
}

TEST_F(caesar_cipher_test, it_should_return_the_expected_decrypted_message_with_a_key_in_range_when_decrypt)
{
    auto output = caesarCipher->decrypt(CIPHERED_MESSAGE, DEFAULT_KEY);
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, output);
}

TEST_F(caesar_cipher_test, it_should_throw_if_a_character_out_of_the_alphabet_is_in_the_input_message_when_encrypt)
{
    try
    {
        caesarCipher->encrypt("***", DEFAULT_KEY);
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

TEST_F(caesar_cipher_test, it_should_throw_if_a_character_out_of_the_alphabet_is_in_the_input_message_when_decrypt)
{
    try
    {
        caesarCipher->encrypt("***", DEFAULT_KEY);
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
