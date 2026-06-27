#include "parser.h"

vector<pair<int, int> > &GenderedData::get(char gender) {
    return gender == 'M' ? M : F; // getter function
}