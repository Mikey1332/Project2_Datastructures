#include "hash.h"
#include "parser.h"
using namespace std;

int HashTable::getFilledSlots() const {
    return filledSlots;
}

int HashTable::getCapacity() const {
    return capacity;
}

bool HashTable::getOccupied(int index) const {
    return buckets[index].occupied;
}

const vector<HashTable::Slot>& HashTable::getBuckets() const {
    return buckets;
}

int HashTable::hash(const string& name) { // this sucks but temporary
    long long index = 0; // overflow fix?
    for (char c : name) {
        index += (long long)(tolower(c) - 'a') * (long long)name.length();
    }
    return (int)index % base;
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

GenderData* HashTable::getData(const string& name) {
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

int HashTable::getYearTotal(string name, char sex, int year, bool pref) {
    GenderData* data = getData(name);
    if (data) { // If found
        return data->getCount(sex,year);
    }
    // If not found
    return 0;
}

vector<pair<string, int>> HashTable::topN(string name, char sex, int n) {
    vector<pair<string, int>> results;
    int minCount = 0;
    int minIndex = 0;

    for (const Slot& slot : buckets) {

        // Skip if empty
        if (!slot.occupied) {
            continue;;
        }
        // Skip if name doesn't not start with prefix
        if (slot.name.substr(0, name.size()) != name) {
            continue;
        }
        // Get total
        int total = getAllTimeTotal(slot.name,sex,true);

        // If vector not full yet
        if ((int)results.size() < n) {
            results.push_back({slot.name, total});

            // After vec is N-sized, find the minimum
            if ((int)results.size() == n) {
                minIndex = 0;
                for (int i = 1; i < n; i++) {
                    if (results[i].second < results[minIndex].second)
                        minIndex = i;
                }
                minCount = results[minIndex].second;
            }

        } else if (total > minCount) {
            // Replace with current minimum
            results[minIndex] = {slot.name, total};

            minIndex = 0;
            for (int i = 1; i < n; i++) {
                if (results[i].second < results[minIndex].second)
                    minIndex = i;
            }
            minCount = results[minIndex].second;
        }
    }

    // sort results before returning

    return results;
}