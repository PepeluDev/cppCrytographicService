#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "trie/trie_language_detector.hpp"

using testing::_;

class trie_language_detector_test : public ::testing::Test
{
public:
    void SetUp() override {
        language_detector = std::make_unique<detectors::trie_language_detector>(words_dictionary);
     };

protected:
    std::unique_ptr<detectors::trie_language_detector> language_detector;

    std::vector<std::string> words_dictionary{
        "THIS","IS","A","SIMPLE","LIST","OF","WORDS","TO","INSERT","AND",
        "SEARCH","IN","THE","TRIE","MATCHES","WITH","THE","BELOW","TEXT",
        "LANGUAGE"};
    const std::string english_text =
    "This is a simple text that we will use to check if the language matches with \
    the one of the words in the list above";
    const std::string spanish_text =
    "Esto es un simple texto que usaremos para comprobar si el lenguaje coincide \
    con el de las palabras de la lista de arriba";
};

TEST_F(trie_language_detector_test, it_should_return_true_if_more_than_60_percent_of_words_are_in_the_trie)
{
    ASSERT_TRUE(language_detector->languageMatches(english_text));
}

TEST_F(trie_language_detector_test, it_should_return_false_if_less_than_60_percent_of_words_are_in_the_trie)
{
    ASSERT_FALSE(language_detector->languageMatches(spanish_text));
}

TEST_F(trie_language_detector_test, it_should_return_false_if_the_input_text_is_empty)
{
    ASSERT_FALSE(language_detector->languageMatches(""));
}
