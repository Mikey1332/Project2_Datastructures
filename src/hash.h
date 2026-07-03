#ifndef COP3530_PROJECT_2_HASH_H
#define COP3530_PROJECT_2_HASH_H
#include "parser.h"
using namespace std;

class HashTable {

    struct Entry {
        string name;
        GenderData data;
    };

public:

    void insert(string name, char sex, int year, int count);
    int getTotal(string name, char sex, bool pref);
    int getYear(string name, char sex, int year);

};

#endif //COP3530_PROJECT_2_HASH_H