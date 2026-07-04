#ifndef COP3530_PROJECT_2_HASH_H
#define COP3530_PROJECT_2_HASH_H
#include <array>
#include "parser.h"
using namespace std;

class HashTable {

    struct Entry {
        string name;
        GenderData data;
        bool occupied;

        Entry() : occupied(false) {}
    };

    int base = 31; // prime
    int capacity = 200003; // i expect just over 100k names
    Entry* table[200003]; // so I'll aim for about 0.5 load
    int numEntries;

    GenderData* getData(string name);

public:

    HashTable() : numEntries(0) {}
    int hash(string name); // prefer private but need public for testing
    void insert(string name, char sex, int year, int count);
    int getYearTotal(string name, char sex, int year);
    int getAllTimeTotal(string name, char sex, bool pref);
};

#endif //COP3530_PROJECT_2_HASH_H