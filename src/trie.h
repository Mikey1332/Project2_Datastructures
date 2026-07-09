#ifndef COP3530_PROJECT_2_TRIE_H
#define COP3530_PROJECT_2_TRIE_H
#include "parser.h"
using namespace std;


class Trie {

    struct TrieNode {
        TrieNode* children[26] = {};
        string name;
        GenderData data;

        // constructor
        TrieNode();
    };

    TrieNode* root;

    int getTotalOfPrefixHelper(TrieNode* node, string name, char sex);
    int getYearTotalOfPrefixHelper(TrieNode* node, string name, char sex, int year);
    void topNHelper(TrieNode *node, char sex, int n, vector<pair<string, int>> &results, int &minCount, int &minIndex);

public:

    Trie();
    // example starter functions below
    void insert(string name, char sex, int year, int count);
    bool search(string name, char sex, int year); // searching to see if a specific name exists, with a corresponding year and sex
    void print(int year); // just a basic print function for maybe all names + gender in a year with their count.
    int getAllTimeTotal(string name, char sex, bool pref);
    int getYearTotal(string name, char sex, int year, bool pref);
    vector<pair<string, int>> topN(string name, char sex, int n);

    // needed a destructor
    ~Trie();
    //helper for destructor
    void clear(TrieNode* curr);
};


#endif //COP3530_PROJECT_2_TRIE_H