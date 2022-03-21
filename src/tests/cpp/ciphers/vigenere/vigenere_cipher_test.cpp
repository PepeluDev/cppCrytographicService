#include "vigenere/vigenere_cipher.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

// A fake shifter implementation is needed, or a mock
// These tests shouldn't be based on a concrete shifter.
#include "english/english_shifter.hpp"

using testing::_;

class vigenere_cipher_test : public ::testing::Test
{
public:
    void SetUp() override
    {
        vigenereCipher = std::make_unique<algorithms::vigenere_cipher>(std::make_shared<shifters::english_shifter>());
    };

protected:
    std::unique_ptr<algorithms::vigenere_cipher> vigenereCipher;
    const std::string PLAIN_TEXT_MESSAGE = "This is a plain test message";
    const std::string CIPHERED_MESSAGE = "Ffsw ge y zpyul diqf kowqmeo";
    const std::string DEFAULT_KEY = "mykey";
};

TEST_F(vigenere_cipher_test, it_should_not_return_an_empty_string_when_encrypt)
{
    auto output = vigenereCipher->encrypt(PLAIN_TEXT_MESSAGE, DEFAULT_KEY);
    ASSERT_FALSE(output.empty());
}

TEST_F(vigenere_cipher_test, it_should_not_return_an_empty_string_when_decrypt)
{
    auto output = vigenereCipher->decrypt(CIPHERED_MESSAGE, DEFAULT_KEY);
    ASSERT_FALSE(output.empty());
}

TEST_F(vigenere_cipher_test, it_should_return_the_same_message_with_an_empty_key_when_decrypt)
{
    auto output = vigenereCipher->decrypt(CIPHERED_MESSAGE, "");
    ASSERT_EQ(CIPHERED_MESSAGE, output);
}

TEST_F(vigenere_cipher_test, it_should_return_the_same_message_with_an_empty_key_when_encrypt)
{
    auto output = vigenereCipher->encrypt(PLAIN_TEXT_MESSAGE, "");
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, output);
}

TEST_F(vigenere_cipher_test, it_should_return_the_expected_encrypted_message_when_encrypt)
{
    auto output = vigenereCipher->encrypt(PLAIN_TEXT_MESSAGE, DEFAULT_KEY);
    ASSERT_EQ(CIPHERED_MESSAGE, output);
}

TEST_F(vigenere_cipher_test, it_should_return_the_expected_decrypted_message_when_decrypt)
{
    auto output = vigenereCipher->decrypt(CIPHERED_MESSAGE, DEFAULT_KEY);
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, output);
}

TEST_F(vigenere_cipher_test, it_should_throw_if_a_character_out_of_the_alphabet_is_in_the_input_message_when_encrypt)
{
    try
    {
        vigenereCipher->encrypt("***", DEFAULT_KEY);
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

TEST_F(vigenere_cipher_test, it_should_throw_if_a_character_out_of_the_alphabet_is_in_the_input_message_when_decrypt)
{
    try
    {
        vigenereCipher->encrypt("***", DEFAULT_KEY);
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

TEST_F(vigenere_cipher_test, it_should_throw_if_a_character_out_of_the_alphabet_is_in_the_input_key_when_encrypt)
{
    try
    {
        vigenereCipher->encrypt(PLAIN_TEXT_MESSAGE, "***");
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const& err)
    {
        EXPECT_EQ(err.what(), std::string("The key contains the \'*\' character which is not in the defined alphabet"));
    }
    catch (...)
    {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST_F(vigenere_cipher_test, it_should_throw_if_a_character_out_of_the_alphabet_is_in_the_input_key_when_decrypt)
{
    try
    {
        vigenereCipher->encrypt(PLAIN_TEXT_MESSAGE, "***");
        FAIL() << "Expected std::invalid_argument";
    }
    catch (std::invalid_argument const& err)
    {
        EXPECT_EQ(err.what(), std::string("The key contains the \'*\' character which is not in the defined alphabet"));
    }
    catch (...)
    {
        FAIL() << "Expected std::invalid_argument";
    }
}
