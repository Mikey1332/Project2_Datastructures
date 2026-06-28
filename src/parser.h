#ifndef COP3530_PROJECT_2_PARSER_H
#define COP3530_PROJECT_2_PARSER_H
#include <string>
#include <vector>
using namespace std;

// functions to parse the files instead of clumping it all in main()
// or anything that can be shared between trie and hash headers

class GenderedData {
    int maleTotal;
    int femaleTotal;
    vector<pair<int,int>> M;
    vector<pair<int,int>> F;
    // instead of using map<>, this class does the same thing
    // see previous commits if you're curious what changed
    /*
         basically like this:
        'M' = {
            {year, count},
            {2019, 19234},
            {2020, 12894}
        }
        'F' = {
            {2019, 19234},
            {2020, 12894},
            etc
        }
        */
    public:
    GenderedData();
    vector<pair<int,int>>& get(char gender); // see .cpp
    void insert(char gender, int year, int count); // see .cpp
    int getTotal(char gender);
};


#endif //COP3530_PROJECT_2_PARSER_H