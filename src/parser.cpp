#include "parser.h"

GenderedData::GenderedData() {
    maleTotal = 0;
    femaleTotal = 0;
}

vector<pair<int, int> > &GenderedData::get(char gender) {
    return gender == 'M' ? M : F; // getter function
}

int GenderedData::getCount(char gender, int year) {
    //Binary Search - O(log(n)) where n is number of years
    if (gender == 'M')
        return getCountHelper(M, year);
    //If gender == 'F'
    return getCountHelper(F, year);
}

int GenderedData::getCountHelper(vector<pair<int, int>> &allYears, int year) {
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
    return -1;
}


void GenderedData::insert(char gender, int year, int count) {
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

void GenderedData::insertInOrder(vector<pair<int, int>> &allYears, int year, int count) {
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

int GenderedData::getTotal(char gender) {
    if (gender == 'M')
        return maleTotal;
    //If gender == 'F'
    return femaleTotal;
}