#include "caesar/caesar_cracker.hpp"

// Mocks will be needed
#include "caesar/caesar_cipher.hpp"
#include "trie/trie_language_detector.hpp"
// Mocks will be needed

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

using testing::_;

class caesar_cracker_test : public ::testing::Test
{
public:
    void SetUp() override
    {
        caesar_cipher = std::make_shared<algorithms::caesar_cipher>();
        language_detector = std::make_shared<detectors::trie_language_detector>(words_dictionary);

        caesar_cracker = std::make_unique<crackers::caesar_cracker>(caesar_cipher, language_detector,
                                                                    most_common_letters_english_language);
    };

protected:
    std::unique_ptr<crackers::caesar_cracker> caesar_cracker;

    // Mocks will be needed
    std::shared_ptr<algorithms::caesar_cipher> caesar_cipher;
    std::shared_ptr<detectors::trie_language_detector> language_detector;

    const std::string PLAIN_TEXT_MESSAGE = "This is a plain test message that we will use to test our cracker";
    const std::string CIPHERED_MESSAGE = "Wklv lv d sodlq whvw phvvdjh wkdw zh zloo xvh wr whvw rxu fudfnhu";
    const std::string IMPOSSIBLE_TO_CRACK = "AN IMPOSIBLE TO CRACK MESSAGE SINCE IT IS NOT ENCRYPTED";

    const std::vector<std::string> words_dictionary{"THIS", "IS",      "A",     "SIMPLE",  "LIST",    "OF",   "WORDS",
                                                    "USE",  "CRACKER", "THAT",  "TO",      "INSERT",  "AND",  "SEARCH",
                                                    "IN",   "THE",     "TRIE",  "MESSAGE", "PLAIN",   "TEST", "MATCHES",
                                                    "WITH", "THE",     "BELOW", "TEXT",    "LANGUAGE"};
    const std::vector<char> most_common_letters_english_language{'E', 'A', 'O', 'I', 'T'};
};

TEST_F(caesar_cracker_test, it_should_return_a_vector_of_possible_keys_based_on_frequency_analysis)
{
    auto possibleKeys = caesar_cracker->getPossibleKeys(CIPHERED_MESSAGE);
    ASSERT_FALSE(possibleKeys.empty());
}

TEST_F(caesar_cracker_test, it_should_return_the_expected_plain_text_message_after_cracking_the_encryption)
{
    auto output = caesar_cracker->crackMessage(CIPHERED_MESSAGE);
    ASSERT_EQ(PLAIN_TEXT_MESSAGE, output);
}

TEST_F(caesar_cracker_test, it_should_return_the_same_string_when_trying_to_crack_an_impossible_to_crack_message)
{
    auto output = caesar_cracker->crackMessage(IMPOSSIBLE_TO_CRACK);
    ASSERT_EQ(IMPOSSIBLE_TO_CRACK, output);
}

TEST_F(caesar_cracker_test, it_should_return_an_empty_string_if_the_input_message_is_empty_when_crackMessage)
{
    auto output = caesar_cracker->getPossibleKeys("");
    ASSERT_TRUE(output.empty());
}

TEST_F(caesar_cracker_test, it_should_return_an_empty_vector_if_the_input_message_is_empty_when_getPossibleKeys)
{
    auto output = caesar_cracker->crackMessage("");
    ASSERT_TRUE(output.empty());
}

TEST_F(caesar_cracker_test,
       it_should_throw_if_a_character_out_of_the_alphabet_is_in_the_input_message_when_crackMessage)
{
    try
    {
        caesar_cracker->crackMessage("****");
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
