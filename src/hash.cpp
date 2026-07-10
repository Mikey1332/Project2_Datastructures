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

unsigned int HashTable::hash(const string& name) {
    long long h = 0; // Fixes overflow
    for (char c : name) {
        h = ((h * base) + (tolower(c) - 'a' + 1)) % capacity;
    }
    return (unsigned int)(h); // Convert back to unsigned int
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

            total += buckets[i].data.getAllTimeTotal(sex);
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

vector<pair<string, int>> HashTable::topN(string name, char sex, int year, int n) {
    if (n <= 0)
        return {};

    vector<pair<string, int>> results;
    int minCount = 0;
    int minIndex = 0;

    for (const Slot& slot : buckets) {

        // Skip if empty or name doesn't not start with prefix
        if (!slot.occupied || (slot.name.substr(0, name.size()) != name)) continue;

        // Get total
        GenderData* data = getData(slot.name);
        int total;
        if (!data) continue;
        //If all time
        if (year == -1)
            total = data->getAllTimeTotal(sex);
        else //If year specific
            total = data->getCount(sex, year);
        if (total <= 0) continue; // Skip names with no records for this gender

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
    // temporarily use sort()
    sort(results.begin(), results.end(), [](const pair<string,int>& a, const pair<string,int>& b) {
         return a.second > b.second;
     });

    return results;
}

vector<pair<int,int>> yearToYearTrend(string name, char sex, bool pref) {
    return {};
}