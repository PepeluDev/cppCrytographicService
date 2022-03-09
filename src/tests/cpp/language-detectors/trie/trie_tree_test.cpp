#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "trie/trie_tree.hpp"

using testing::_;

class trie_tree_test : public ::testing::Test
{
public:
    void SetUp() override {
        trie = std::make_unique<detectors::trie_tree>();
     };

protected:
    std::unique_ptr<detectors::trie_tree> trie;

    std::vector<std::string> words_dictionary{
        "THIS","IS","A","SIMPLE","LIST","OF","WORDS","TO","INSERT","AND",
        "SEARCH","IN","THE","TRIE","MATCHES","WITH","THE","BELOW","TEXT",
        "LANGUAGE"};
};

TEST_F(trie_tree_test, it_should_be_empty_after_creation)
{
    ASSERT_TRUE(trie->isEmpty());
}

TEST_F(trie_tree_test, it_should_not_be_empty_after_a_word_is_added)
{
    trie->addWord("WATHEVER");
    ASSERT_FALSE(trie->isEmpty());
}

TEST_F(trie_tree_test, it_should_not_contain_an_empty_string)
{
    trie->addWord("");
    ASSERT_FALSE(trie->containsWord(""));
}

TEST_F(trie_tree_test, it_should_contain_an_inserted_word)
{
    trie->addWord("WATHEVER");
    ASSERT_TRUE(trie->containsWord("WATHEVER"));
}

TEST_F(trie_tree_test, it_should_not_contain_a_non_inserted_word)
{
    trie->addWord("WATHEVER");
    ASSERT_FALSE(trie->containsWord("WHOEVER"));
}

TEST_F(trie_tree_test, it_should_contain_every_inserted_word)
{
    trie->addWords(words_dictionary);

    for(auto word: words_dictionary){
        EXPECT_TRUE(trie->containsWord(word));
    }
}
