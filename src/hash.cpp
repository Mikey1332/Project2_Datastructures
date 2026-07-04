#include "hash.h"
#include "parser.h"
using namespace std;

int HashTable::hash(string name) {
    long long index = 0; // overflow fix?
    for (char c : name) {
        index += (long long)(tolower(c) - 'a') * (long long)name.length(); // same type
    }
    return (int)index; // idk how well this works
}

void HashTable::insert(string name, char sex, int year, int count) {
    int index = hash(name);

    for (int i = 0; i < capacity; i++) {

        int probe = (index + i * i) % capacity; // quadratic probing

        if (!buckets[probe].occupied) { // if unoccupied create new slot
            buckets[probe].name = name; // update name
            buckets[probe].data.insert(sex, year, count); // GenderData insert function

            buckets[probe].occupied = true; // update to occupied
            filledSlots++; // increase for new slot
            return;
        }
        if (buckets[probe].name == name) { // update existing data
            buckets[probe].data.insert(sex, year, count); // GenderData insert function
            return;
        }
    }
}

GenderData* HashTable::getData(string name) { // helper for future functions
    int index = hash(name);
    for (int i = 0; i < capacity; i++) {
        int probe = (index + i * i) % capacity;
        if (!buckets[probe].occupied)
            return nullptr;
        if (buckets[probe].name == name)
            return &buckets[probe].data;
    }
    return nullptr;
}

int HashTable::getFilledSlots() {
    return filledSlots;
}

int HashTable::getAllTimeTotal(string name, char sex, bool pref) {
    if (pref) {
        // search prefix
        return 0; // fix later
    }
    GenderData* data = getData(name);
    return data->getAllTimeTotal(sex);
}

int HashTable::getYearTotal(string name, char sex, int year) {
    GenderData* data = getData(name);
    if (data) { // If found
        return data->getCount(sex,year);
    }
    // If not found return -1
    return -1;
}