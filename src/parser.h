#ifndef COP3530_PROJECT_2_PARSER_H
#define COP3530_PROJECT_2_PARSER_H
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;


class GenderData {

    int maleTotal = 0;
    int femaleTotal = 0;
    vector<pair<int,int>> M = {};
    vector<pair<int,int>> F = {};

    void insertInOrder(vector<pair<int, int>> &allYears, int year, int count);
    int getCountHelper(vector<pair<int, int>> &allYears, int year);

public:

    GenderData();
    vector<pair<int,int>>& get(char gender);
    int getCount(char gender, int year);
    void insert(char gender, int year, int count);
    int getAllTimeTotal(char gender);

    // below are file parsing functions for me - Alex

    void loadData();
    /* file parsing doesn't really belong with GenderData, GenderData was initially a struct to replace
    a map. the two aren't related. i can ask the professor if we can use this as a map because it isn't
    the data structure we're comparing and it's used by both structures. when I put GenderData at the top
    of this file, it was just so it wouldn't have to be written twice in both files.

    if it's clearer what i mean it can be a separate file like "shared" or something, but if it's just
    the one struct/class then that's kinda extra, so that's why i put it here. it's not file parsing.
    */
};


#endif //COP3530_PROJECT_2_PARSER_H