#ifndef COP3530_PROJECT_2_PARSER_H
#define COP3530_PROJECT_2_PARSER_H
#include <string>
#include <vector>
using namespace std;


class GenderedData {
    int maleTotal = 0;
    int femaleTotal = 0;
    vector<pair<int,int>> M = {};
    vector<pair<int,int>> F = {};

    void insertInOrder(vector<pair<int, int>> &allYears, int year, int count);
    int getCountHelper(vector<pair<int, int>> &allYears, int year);
    public:
    GenderedData();
    vector<pair<int,int>>& get(char gender);
    int getCount(char gender, int year);
    void insert(char gender, int year, int count);
    int getTotal(char gender);
};


#endif //COP3530_PROJECT_2_PARSER_H