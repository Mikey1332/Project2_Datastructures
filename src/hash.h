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

    int base;
    int filledSlots;
    int capacity;
    vector<Slot> buckets;
    // Expected ~100k names, target load factor ~0.5
    GenderData* getData(const string &name);

public:

    HashTable() : base(31), filledSlots(0), capacity(200003) {
        buckets.resize(capacity);
    }

    // Read-only getters
    int getFilledSlots() const;
    int getCapacity() const;
    bool getOccupied(int index) const;
    const vector<Slot>& getBuckets() const;

    int hash(const string& name);
    void insert(string name, char sex, int year, int count);
    int getAllTimeTotal(string name, char sex, bool pref);
    int getYearTotal(string name, char sex, int year, bool pref);
    vector<pair<string, int>> topN(string name, char sex, int n);
};

#endif //COP3530_PROJECT_2_HASH_H