#include "parser.h"

GenderedData::GenderedData() {
    maleTotal = 0;
    femaleTotal = 0;
}

vector<pair<int, int> > &GenderedData::get(char gender) {
    return gender == 'M' ? M : F; // getter function
}

void GenderedData::insert(char gender, int year, int count) {
    if (gender == 'M') {
        maleTotal += count;
        M.push_back({year, count});
    }
    else { //If gender == 'F'
        femaleTotal += count;
        F.push_back({year, count});
    }
}

int GenderedData::getTotal(char gender) {
    if (gender == 'M')
        return maleTotal;
    //If gender == 'F'
    return femaleTotal;
}