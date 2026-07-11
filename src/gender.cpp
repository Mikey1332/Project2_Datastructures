#include "gender.h"
#include "trie.h"
#include "hash.h"
#include <iostream>

GenderData::GenderData() {
    maleTotal = 0;
    femaleTotal = 0;
}

const vector<pair<int, int>>& GenderData::get(char gender) const{
    if (gender == 'M')
        return M;
    if (gender == 'F')
        return F;
    return A;
}

void GenderData::createCombined() {
    A.clear();
    int i = 0;
    int j = 0;
    while (i < M.size() && j < F.size()) {
        if (M[i].first == F[j].first) {
            A.emplace_back(M[i].first, M[i].second + F[j].second);
            i++;
            j++;
        }
        else if (M[i].first < F[j].first) {
            A.push_back(M[i]);
            i++;
        }
        else {
            A.push_back(F[j]);
            j++;
        }
    }
    while (i < M.size()) {
        A.push_back(M[i]);
        i++;
    }
    while (j < F.size()) {
        A.push_back(F[j]);
        j++;
    }
}

int GenderData::getCount(char gender, int year) const {
    //Binary Search - O(log(n)) where n is number of years
    if (gender == 'M')
        return getCountHelper(M, year);
    if (gender == 'F')
        return getCountHelper(F, year);
    //If gender == 'A'
    return getCountHelper(M, year) + getCountHelper(F, year);
}

int GenderData::getCountHelper(const vector<pair<int, int>> &allYears, int year) const {
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
    createCombined();
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

int GenderData::getAllTimeTotal(char gender) const{
    if (gender == 'M')
        return maleTotal;
    if (gender == 'F')
        return femaleTotal;
    //If gender == 'A'
    return maleTotal + femaleTotal;
}