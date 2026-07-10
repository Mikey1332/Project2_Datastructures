#ifndef COP3530_PROJECT_2_LOAD_H
#define COP3530_PROJECT_2_LOAD_H
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "trie.h"
#include "hash.h"

using namespace std;

struct Parser {
    Parser();
    void insertTrie(Trie& trie);
    void insertHash(HashTable& hashTable);
};
#endif
