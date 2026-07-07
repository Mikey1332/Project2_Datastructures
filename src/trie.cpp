#include "trie.h"

// constructor for TrieNode
Trie::TrieNode::TrieNode() {
    isName = false;
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(string name, char sex, int year, int count) {
    TrieNode* curr = root;
    for (int i  = 0; i < int(name.length()); i++) {
        //This line can break if name has non-letter
        int index = tolower(name[i]) - 'a';
        if (curr->children[index] == nullptr)
            curr->children[index] = new TrieNode();
        curr = curr->children[index];
    }
    //Curr is last element, so give it all the data
    curr->isName = true;
    curr->data.insert(sex, year, count);
}

int Trie::getAllTimeTotal(string name, char sex, bool pref) {
    if (root == nullptr)
        return 0;
    TrieNode* curr = root;
    for (int i  = 0; i < int(name.length()); i++) {
        int index = tolower(name[i]) - 'a';
        curr = curr->children[index];
        if (curr == nullptr)
            return 0;
    }
    //If it is not for a prefix, return total for exact name
    if (pref == false) {
        if (curr->isName)
            return curr->data.getAllTimeTotal(sex);
        return 0;
    }
    //If it is a prefix
    return getTotalOfPrefixHelper(curr, name, sex);
}

int Trie::getTotalOfPrefixHelper(TrieNode* node, string name, char sex) {
    //This goes through each letter for each node, even if it's not a child
    if (node == nullptr)
        return 0;
    int total = 0;
    if (node->isName)
        total+=node->data.getAllTimeTotal(sex);
    for (TrieNode* child : node->children)
        total += getTotalOfPrefixHelper(child, name, sex);
    return total;
}

int Trie::getYearTotal(string name, char sex, int year) {
    TrieNode* curr = root;
    for (int i  = 0; i < int(name.length()); i++) {
        int index = tolower(name[i]) - 'a';
        curr = curr->children[index];
    }
    return curr->data.getCount(sex, year);
    //Returns -1 if year is not found
}

// destructor for Trie
void Trie::clear(TrieNode* curr) {
    if (curr == nullptr) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        clear(curr->children[i]);
    }
    delete curr;
}

Trie::~Trie() {
    clear(root);
}