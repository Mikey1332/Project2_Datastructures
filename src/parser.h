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
};

struct Parser {
    // below are file parsing functions for me - Alex

    void loadData();
    /* file parsing doesn't really belong with GenderData, GenderData was initially a
    class to replace a map, the two aren't related. when I put GenderData at the top
    of this file, it was just so it wouldn't have to be written twice in both files.
    So a separate class would work better.
    */
};


#endif //COP3530_PROJECT_2_PARSER_H