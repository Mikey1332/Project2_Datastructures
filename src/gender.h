#ifndef COP3530_PROJECT_2_PARSER_H
#define COP3530_PROJECT_2_PARSER_H
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm> // temporary

using namespace std;

class GenderData {
    int maleTotal = 0;
    int femaleTotal = 0;
    vector<pair<int,int>> M = {};
    vector<pair<int,int>> F = {};
    vector<pair<int,int>> A = {};

    void insertInOrder(vector<pair<int, int>> &allYears, int year, int count);
    int getCountHelper(const vector<pair<int, int>> &allYears, int year) const;
    void createCombined();

public:

    GenderData();
    vector<pair<int,int>>& get(char gender) const;
    int getCount(char gender, int year) const;
    void insert(char gender, int year, int count);
    int getAllTimeTotal(char gender) const;
};

#endif //COP3530_PROJECT_2_PARSER_H