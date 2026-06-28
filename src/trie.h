#ifndef COP3530_PROJECT_2_TRIE_H
#define COP3530_PROJECT_2_TRIE_H
#include "parser.h"
using namespace std;

// hi just making a skeleton of what kind of functions there might be
// that way i can start writing tests for everyone to use

class Trie {

    struct TrieNode {
        TrieNode* children[26] = {}; // 26 letters (A-Z)
        bool isName = false;

        // fills in data only if isname true
        GenderedData data; // see parser.h

        // constructor
        TrieNode();
    };

    TrieNode* root;

public:

    Trie();
    // example starter functions below
    void insert(string name, char sex, int year, int count);
    int getTotal(string name, char sex);
    int getYear(string name, char sex, int year);

    // needed a destructor
    ~Trie();
    //helper for destructor
    void clear(TrieNode* curr);
};


#endif //COP3530_PROJECT_2_TRIE_H