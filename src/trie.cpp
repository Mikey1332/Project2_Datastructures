#include "trie.h"

// constructor for Node

Trie::Node::Node() {
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::Trie() {
    root = new Node();
}

// destructor for Trie
void Trie::clear(Node* curr) {
    if (curr = nullptr) { 
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