#include "hash.h"
#include "parser.h"
using namespace std;

int HashTable::hash(string name) {
    int index = 0;

    // gotta come up with a good hash that risks fewer collisions

    return index % capacity;
}

void HashTable::insert(string name, char sex, int year, int count) {
    int index = hash(name);

    for (int i = 0; i < capacity; i++) {

        int probe = (index + i * i) % capacity; // quadratic probing

        if (!table[probe]->occupied) { // if unoccupied create new slot
            table[probe]->name = name; // update name
            table[probe]->data.insert(sex, year, count); // GenderData insert function

            table[probe]->occupied = true; // update to occupied
            numEntries++;
            return;
        }
        if (table[probe]->name == name) { // update existing data
            table[probe]->data.insert(sex, year, count); // GenderData insert function
            numEntries++;
            return;
        }
    }
}

GenderData* HashTable::getData(string name) { // helper for future functions
    int index = hash(name);
    for (int i = 0; i < capacity; i++) {
        int probe = (index + i * i) % capacity;
        if (!table[probe]->occupied)
            return nullptr;
        if (table[probe]->name == name)
            return &table[probe]->data;
    }
    return nullptr;
}

int HashTable::getYearTotal(string name, char sex, int year) {
    GenderData* data = getData(name);
    if (data) { // if found
        // return total for that year/sex
        return 0; // fix
        // i finish tomorrow
    }
    // if not found return -1
    return -1;
}