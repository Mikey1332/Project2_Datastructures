#ifndef COP3530_PROJECT_2_TRIE_H
#define COP3530_PROJECT_2_TRIE_H
#include "parser.h"
using namespace std;


class Trie {

    struct TrieNode {
        TrieNode* children[26] = {};
        bool isName;

        GenderedData data;

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