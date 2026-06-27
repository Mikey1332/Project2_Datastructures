#ifndef COP3530_PROJECT_2_HASH_H
#define COP3530_PROJECT_2_HASH_H
// #include "parser.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

class HashTable {

    struct Entry {
        string name;
        map<char, vector<pair<int,int>>> data; // same concept as in trie
    };

public:

    void insert(string name, char sex, int year, int count);
    int getTotal(string name, char sex);
    int getYear(string name, char sex, int year);

};

#endif //COP3530_PROJECT_2_HASH_H