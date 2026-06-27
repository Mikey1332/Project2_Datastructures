#ifndef COP3530_PROJECT_2_TRIE_H
#define COP3530_PROJECT_2_TRIE_H
#include <map>
#include <string>
#include <vector>
using namespace std;
// #include "parser.h" idk if this will be used by trie/hash or only by main

// hi just making a skeleton of what kind of functions there might be
// that way i can start writing tests for everyone to use

class Trie {

    struct Node {
        Node* children[26] = {}; // 26 letters (A-Z)
        bool isName = false;

        // fills in data only if isname true
        map<char, vector<pair<int,int>>> data; // map with gender key and (year,count) vector
        /*
         basically like this:
        'M' = {
            {year, count},
            {2019, 19234},
            {2020, 12894}
        }
        'F' = {
            {2019, 19234},
            {2020, 12894},
            etc
        }
        */

        // because how else do we separate male and female if they have different info
        // lemme know what you think about using a map

        Node();
    };

    Node* root;

public:

    Trie();
    // example starter functions below
    void insert(string name, char sex, int year, int count);
    int getTotal(string name, char sex);
    int getYear(string name, char sex, int year);

};


#endif //COP3530_PROJECT_2_TRIE_H