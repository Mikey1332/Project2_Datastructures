#include "trie.h"

Trie::TrieNode::TrieNode() {
    name = "";
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(string name, char sex, int year, int count) {
    TrieNode* curr = root;
    for (int i  = 0; i < int(name.length()); i++) {
        //This line can break if name has non-letter
        int index = tolower(name[i]) - 'a';
        if (curr->children[index] == nullptr)
            curr->children[index] = new TrieNode();
        curr = curr->children[index];
    }
    //Curr is last element, so give it all the data
    curr->name = name;
    curr->data.insert(sex, year, count);
}

int Trie::getAllTimeTotal(string name, char sex, bool pref) {
    if (root == nullptr)
        return 0;
    TrieNode* curr = root;
    for (int i  = 0; i < int(name.length()); i++) {
        int index = tolower(name[i]) - 'a';
        curr = curr->children[index];
        if (curr == nullptr)
            return 0;
    }
    //If it is not for a prefix, return total for exact name
    if (pref == false) {
        if (!curr->name.empty())
            return curr->data.getAllTimeTotal(sex);
        return 0;
    }
    //If it is a prefix
    return getTotalOfPrefixHelper(curr, sex);
}

int Trie::getTotalOfPrefixHelper(TrieNode* node, char sex) {
    if (node == nullptr)
        return 0;
    int total = 0;
    if (!node->name.empty())
        total+=node->data.getAllTimeTotal(sex);
    for (TrieNode* child : node->children) {
        if (child) // Only do it if child!
            total += getTotalOfPrefixHelper(child, sex);
    }
    return total;
}

int Trie::getYearTotal(string name, char sex, int year, bool pref) {
    if (root == nullptr)
        return 0;
    TrieNode* curr = root;
    for (int i  = 0; i < int(name.length()); i++) {
        int index = tolower(name[i]) - 'a';
        curr = curr->children[index];
        if (curr == nullptr)
            return 0;
    }
    //If it is not for a prefix, return total for exact name
    if (pref == false) {
        if (!curr->name.empty())
            return curr->data.getCount(sex, year);
        return 0;
    }
    //If it is a prefix
    return getYearTotalOfPrefixHelper(curr, sex, year);
}

int Trie::getYearTotalOfPrefixHelper(TrieNode* node, char sex, int year) {
    //This goes through each letter for each node, even if it's not a child
    if (node == nullptr)
        return 0;
    int total = 0;
    if (!node->name.empty())
        total+=node->data.getCount(sex, year);
    for (TrieNode* child : node->children)
        total += getYearTotalOfPrefixHelper(child, sex, year);
    return total;
}

vector<pair<string, int>> Trie::topN(string name, char sex, int year, int n) {
    if (n <= 0)
        return {};

    vector<pair<string, int>> results;
    int minCount = 0;
    int minIndex = 0;

    TrieNode* curr = root;
    for (char c : name) {
        int index = tolower(c) - 'a';
        if (!curr->children[index]) {
            // Does not exist, return empty
            return results;
        }
        curr = curr->children[index];
    }

    topNHelper(curr, sex, year, n, results, minCount, minIndex);

    // sort results before returning
    // temporarily use sort()
    sort(results.begin(), results.end(), [](const pair<string,int>& a, const pair<string,int>& b) {
         return a.second > b.second;
     });

    return results;
}

void Trie::topNHelper(TrieNode* node, char sex, int year, int n, vector<pair<string, int>>& results, int& minCount, int& minIndex) {
    if (!node)
        return;
    int total = 0;
    // If node is name
    if (!node->name.empty()) {
        //If all time
        if (year == -1)
            total = node->data.getAllTimeTotal(sex);
        else
            total = node->data.getCount(sex, year);

        if (total > 0) { // Only use names with data for this gender

            // If vector not full yet
            if ((int)results.size() < n) {
                results.push_back({node->name, total});

                if ((int)results.size() == n) {
                    minIndex = 0;
                    for (int i = 1; i < n; i++) {
                        if (results[i].second < results[minIndex].second)
                            minIndex = i;
                    }
                    minCount = results[minIndex].second;
                }
            }
            else if (total > minCount) {
                // Replace with current minimum
                results[minIndex] = {node->name, total};

                minIndex = 0;
                for (int i = 1; i < n; i++) {
                    if (results[i].second < results[minIndex].second)
                        minIndex = i;
                }
                minCount = results[minIndex].second;
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        topNHelper(node->children[i], sex, year, n, results, minCount, minIndex);
    }
}

vector<pair<int,int>> Trie::yearToYearTrend(string name, char sex, bool pref) {
    vector<pair<int,int>> results = {};
    if (root == nullptr)
        return {};
    TrieNode* curr = root;
    for (int i  = 0; i < int(name.length()); i++) {
        int index = tolower(name[i]) - 'a';
        curr = curr->children[index];
        if (curr == nullptr)
            return {};
    }
    //If it is not for a prefix, return total for exact name
    if (!pref) {
        if (!curr->name.empty())
            return curr->data.get(sex);
        return {};
    }
    //If it is a prefix
    yearToYearTrendHelper(curr, sex, results);
    return results;
}

void Trie::yearToYearTrendHelper(TrieNode* node, char sex, vector<pair<int, int>>& results) {
    if (node == nullptr)
        return;
    if (!node->name.empty()) {
        for (const pair<int, int>& p: node->data.get(sex)) {
            bool found = false;
            for (pair<int, int>& result : results) {
                if (p.first == result.first) {
                    result.second += p.second;
                    found = true;
                    break;
                }
            }
            if (!found)
                results.push_back(p);
        }
    }
    for (TrieNode* child : node->children)
        yearToYearTrendHelper(child, sex, results);
}

void Trie::clear(TrieNode* curr) {
    if (curr == nullptr) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        clear(curr->children[i]);
    }
    delete curr;
}

Trie::~Trie() {
    clear(root);
}