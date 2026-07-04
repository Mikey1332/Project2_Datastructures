#include "hash.h"
#include "parser.h"
using namespace std;

int HashTable::getFilledSlots() {
    return filledSlots;
}

int HashTable::getCapacity() {
    return capacity;
}

bool HashTable::getOccupied(int index) {
    return buckets[index].occupied;
}

int HashTable::hash(string name) { // this sucks but temporary
    long long index = 0; // overflow fix?
    for (char c : name) {
        index += (long long)(tolower(c) - 'a') * (long long)name.length();
    }
    return (int)index;
}

void HashTable::insert(string name, char sex, int year, int count) {
    int index = hash(name);

    for (int i = 0; i < capacity; i++) {
        // Quadratic probing
        int probe = (index + i * i) % capacity;

        // If unoccupied
        if (!buckets[probe].occupied) {

            buckets[probe].name = name;
            buckets[probe].data.insert(sex, year, count);
            buckets[probe].occupied = true;
            filledSlots++;
            return;
        }
        // If name found
        if (buckets[probe].name == name) {
            // Update data
            buckets[probe].data.insert(sex, year, count);
            return;
        }
    }
}

GenderData* HashTable::getData(string name) {
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

// Find the all-time total occurrences per sex, either searching by exact name or by a prefix
int HashTable::getAllTimeTotal(string name, char sex, bool pref) {

    if (pref) {
        string prefix = name;
        int total = 0;

        for (int i = 0; i < capacity; i++) {

            // Skip if unoccupied
            if (!buckets[i].occupied) {
                continue;
            }
            // Skip if name < prefix
            if ((int)buckets[i].name.length() < (int)prefix.length()) {
                continue;
            }

            bool matches = true;
            for (int j = 0; j < (int)prefix.length(); j++) {
                if (buckets[i].name[j] != prefix[j]) {
                    matches = false;
                    break; // Stop checking this name
                }
            }

            if (!matches) {
                continue;
                // Skip to next buckets[i]
            }

            GenderData* data = getData(buckets[i].name);
            total += data->getAllTimeTotal(sex);
        }

        return total;
    }
    // Else "name" is the exact name to search
    GenderData* data = getData(name);
    if (!data) {
        return 0;
    }
    return data->getAllTimeTotal(sex);
}

int HashTable::getYearTotal(string name, char sex, int year) {
    GenderData* data = getData(name);
    // if (data) { // If found
    //     return data->getCount(sex,year);
    // }
    // // If not found
    // return 0;
    return data->getCount(sex,year);
}