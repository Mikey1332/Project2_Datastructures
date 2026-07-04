#ifndef COP3530_PROJECT_2_HASH_H
#define COP3530_PROJECT_2_HASH_H
#include <array>
#include "parser.h"
using namespace std;

class HashTable {

    struct Slot {
        string name;
        GenderData data;
        bool occupied;

        Slot() : occupied(false) {}
    };

    int base; // prime
    int filledSlots;
    int capacity; // i expect just over 100k names
    vector<Slot> buckets; // so I'll aim for about 0.5 load

    GenderData* getData(string name);

public:

    HashTable() : base(31), filledSlots(0), capacity(200003) {}
    int hash(string name); // prefer private but need public for testing
    void insert(string name, char sex, int year, int count);
    int getYearTotal(string name, char sex, int year);
    int getAllTimeTotal(string name, char sex, bool pref);
};

#endif //COP3530_PROJECT_2_HASH_H