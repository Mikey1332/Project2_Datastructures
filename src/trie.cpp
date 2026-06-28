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
    for (int i  = 0; i < name.length(); i++) {
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

int Trie::getTotal(string name, char sex) {
    TrieNode* curr = root;
    for (int i  = 0; i < name.length(); i++) {
        int index = tolower(name[i]) - 'a';
        curr = curr->children[index];
    }
    return curr->data.getTotal(sex);
}

int Trie::getYear(string name, char sex, int year) {
    TrieNode* curr = root;
    for (int i  = 0; i < name.length(); i++) {
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