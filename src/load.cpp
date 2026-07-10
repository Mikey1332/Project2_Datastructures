#include "load.h"



Parser::Parser() {
    ofstream outFile("../data/data.txt"); // for both insert functions to grab from evenly.
    for(int year = 1880; year < 2026; year++) {
        string year_str = to_string(year);
        ifstream file("../data/names/yob" + year_str + ".txt");
        if (!file.is_open()) {
            cout << year_str << " not found" << endl;
            return; // maybe to add something else for test.cpp but for now this is fine.
        }
        string line;

        while(getline(file, line)) {
            stringstream ss(line);
            string name;
            string genderStr;
            string countStr;
            if(getline(ss, name, ',') && getline(ss, genderStr, ',') && getline(ss, countStr, ',')) {
                outFile << name + "," + genderStr << "," << countStr << "," << year_str << endl;
            }
        }
    }
}
void Parser::insertHash(HashTable& hash) {
    ifstream file("../data/data.txt");
    string line;
    while(getline(file, line)) {
        stringstream ss(line);
        string name;
        string genderStr;
        string countStr;
        string yearStr;
        if(getline(ss, name, ',') && getline(ss, genderStr, ',') && getline(ss, countStr, ',') && getline(ss, yearStr, '.')) {
            char gender = genderStr[0];
            int count = stoi(countStr);
            int year = stoi(yearStr);
            hash.insert(name, gender, year, count);
        }
    }
}

void Parser::insertTrie(Trie& trie) {
    ifstream file("../data/data.txt");
    string line;
    while(getline(file, line)) {
        stringstream ss(line);
        string name;
        string genderStr;
        string countStr;
        string yearStr;
        if(getline(ss, name, ',') && getline(ss, genderStr, ',') && getline(ss, countStr, ',') && getline(ss, yearStr, '.')) {
            char gender = genderStr[0];
            int count = stoi(countStr);
            int year = stoi(yearStr);
            trie.insert(name, gender, year, count);
        }
    }
}