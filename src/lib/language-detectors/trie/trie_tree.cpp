#include "trie_tree.hpp"

#include <map>
#include <string>
#include <utility>
#include <vector>

namespace detectors
{
bool trie_tree::containsWord(const std::string& word) const
{
    if (this->isEmpty())
    {
        return false;
    }
    auto trieNode = this->root;
    for (std::string::size_type i = 0; i < word.length(); i++)
    {
        auto upperChar = std::toupper(word[i]);
        if (trieNode == nullptr || !trieNode->containsChar(upperChar))
        {
            return false;
        }
        trieNode = trieNode->getBranchNode(upperChar);
    }
    return trieNode->leaf;
}

bool trie_tree::isEmpty() const
{
    return this->root->charBranches.empty();
}

void trie_tree::addWord(const std::string& word)
{
    if (word.empty())
    {
        return;
    }
    auto trieNode = this->root;
    for (std::string::size_type i = 0; i < word.length(); i++)
    {
        auto upperChar = std::toupper(word[i]);
        if (trieNode->containsChar(upperChar))
        {
            trieNode = trieNode->getBranchNode(upperChar);
        }
        else
        {
            auto newTrieNode = new TrieNode();
            trieNode->charBranches.insert(std::pair<char, TrieNode*>(upperChar, newTrieNode));
            trieNode = newTrieNode;
        }
    }
    trieNode->leaf = true;
}

void trie_tree::addWords(const std::vector<std::string>& words)
{
    for (auto word : words)
    {
        this->addWord(word);
    }
}

}  // namespace detectors