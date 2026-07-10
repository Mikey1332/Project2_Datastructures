#include "parser.h"
#include "trie.h"
#include "hash.h"
#include <iostream>

GenderData::GenderData() {
    maleTotal = 0;
    femaleTotal = 0;
}

vector<pair<int, int>> &GenderData::get(char gender) {
    if (gender == 'M')
        return M;
    if (gender == 'F')
        return F;
    vector<pair<int, int>> combined = M;
    for (pair<int, int> p : F) {
        combined.push_back(p);
    }
    return combined;
}

int GenderData::getCount(char gender, int year) {
    //Binary Search - O(log(n)) where n is number of years
    if (gender == 'M')
        return getCountHelper(M, year);
    if (gender == 'F')
        return getCountHelper(F, year);
    //If gender == 'A'
    return getCountHelper(M, year) + getCountHelper(F, year);
}

int GenderData::getCountHelper(vector<pair<int, int>> &allYears, int year) {
    //Binary Search - O(log(n)) where n is number of years
    int first = 0;
    int last = allYears.size()-1;
    while (first <= last) {
        int mid = (first+last)/2;
        if (allYears[mid].first < year) {
            first = mid+1;
        }
        else if (allYears[mid].first > year) {
            last = mid-1;
        }
        else {
            //If year is found
            return allYears[mid].second;
        }
    }
    //Year not found:
    return 0;
}


void GenderData::insert(char gender, int year, int count) {
    //O(n)
    if (gender == 'M') {
        maleTotal += count;
        //Inserts it in order
        insertInOrder(M, year, count);
    }
    else { //If gender == 'F'
        femaleTotal += count;
        insertInOrder(F, year, count);
    }
}

void GenderData::insertInOrder(vector<pair<int, int>> &allYears, int year, int count) {
    int first = 0;
    int last = allYears.size()-1;
    while (first <= last) {
        int mid = (first+last)/2;
        if (allYears[mid].first < year) {
            first = mid+1;
        }
        else if (allYears[mid].first > year) {
            last = mid-1;
        }
        else {
            //re-insert (override count)
            allYears[mid].second = count;
            return;
        }
    }
    allYears.insert(allYears.begin() + first, {year, count});
}

int GenderData::getAllTimeTotal(char gender) {
    if (gender == 'M')
        return maleTotal;
    if (gender == 'F')
        return femaleTotal;
    //If gender == 'A'
    return maleTotal + femaleTotal;
}

// file parsing logic, would work only if exe of main.cpp is located outside of any folder since it is relative. - update if main exe is not.
// rn the main.exe file path is being sent into cmake-build-debug, so its rn: ../data/names; but if someone moves it, this wont work.
/*
void GenderData::loadData() {
    ofstream outFile("../test/test_textFromData.txt"); // for test purposes
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
                char gender = genderStr[0];
                int count = stoi(countStr);
                insert(gender, year, count);
                outFile << name + ", " + genderStr << ", " << count << ", " << year << endl;
            }
        }
    }
}

outdated, was better to make a separate struct in load.h and load.cpp so that way its possible to have to separate insert functions and testing their time for each structure.
*/
