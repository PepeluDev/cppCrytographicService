#pragma once

#include <string>
#include <map>
#include <vector>

namespace detectors {

typedef struct TrieNode TrieNode;

struct TrieNode {
    TrieNode()=default;

    TrieNode(const TrieNode& t) = delete;
    TrieNode(TrieNode&& t) = delete;
    TrieNode& operator=(const TrieNode& t) = delete;
    TrieNode& operator=( TrieNode&& t) = delete;

    ~TrieNode(){
        for(auto branch: charBranches){
            delete branch.second;
        }
    }

    std::map<char,TrieNode*> charBranches;
    bool leaf = false;

    bool containsChar(char c){
        return charBranches.find(c) != charBranches.end();
    }
    TrieNode* getBranchNode(char c){
        auto charBranch = charBranches.find(c);
        return charBranch != charBranches.end() ? charBranch->second : nullptr;
    }
};

class trie_tree
{
private:
    TrieNode* root = new TrieNode();
public:
    trie_tree() = default;

    trie_tree(const trie_tree& t) = delete;
    trie_tree(trie_tree&& t) = delete;
    trie_tree& operator=(const trie_tree& t) = delete;
    trie_tree& operator=( trie_tree&& t) = delete;

    ~trie_tree(){
        delete root;
    }

    bool containsWord(const std::string& word) const;
    bool isEmpty() const;
    void addWord(const std::string& word);
    void addWords(const std::vector<std::string>& words);

};

}