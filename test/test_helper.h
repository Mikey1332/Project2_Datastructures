#ifndef COP3530_PROJECT_2_TEST_HELPERS_H
#define COP3530_PROJECT_2_TEST_HELPERS_H
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "hash.h"
#include "parser.h"
#include "trie.h"


inline Trie makeTestTrie() {
    Trie trie;

    trie.insert("Albert",   'M', 2020, 500);
    trie.insert("Albert",   'M', 2021, 700);
    trie.insert("Liam",     'M', 2019, 700);
    trie.insert("Liam",     'M', 2020, 680);
    trie.insert("Liam",     'M', 2021, 660);
    trie.insert("Bob",      'M', 2019, 1000);
    trie.insert("Bob",      'M', 2020, 580);
    trie.insert("Sam",      'M', 2019, 200);
    trie.insert("Sam",      'F', 2019, 150);
    trie.insert("Samuel",   'M', 2000, 950);
    trie.insert("Samantha", 'F', 2019, 700);
    trie.insert("Emma",     'F', 2019, 500);
    trie.insert("Emma",     'F', 2020, 480);
    trie.insert("Emma",     'F', 2021, 460);
    trie.insert("Emily",    'F', 2019, 300);
    trie.insert("Benjamin", 'M', 2019, 600);
    trie.insert("Benjamin", 'M', 2020, 580);
    trie.insert("Benny",    'M', 2019, 100);
    trie.insert("Brad",     'M', 2019, 250);
    trie.insert("Brett",    'M', 2019, 90);

    return trie;
}

inline HashTable makeTestHash() {
    HashTable hash;

    hash.insert("Albert",   'M', 2020, 500);
    hash.insert("Albert",   'M', 2021, 700); // Albert 1200
    hash.insert("Liam",     'M', 2019, 700);
    hash.insert("Liam",     'M', 2020, 680);
    hash.insert("Liam",     'M', 2021, 660); // Liam 2040
    hash.insert("Bob",      'M', 2019, 1000);
    hash.insert("Bob",      'M', 2020, 580); // Bob 1580
    hash.insert("Sam",      'M', 2019, 200);
    hash.insert("Sam",      'F', 2019, 150); // Sam M+F 350
    hash.insert("Samuel",   'M', 2000, 950);
    hash.insert("Samantha", 'F', 2019, 700);
    hash.insert("Emma",     'F', 2019, 500);
    hash.insert("Emma",     'F', 2020, 480);
    hash.insert("Emma",     'F', 2021, 460); // Emma 1440
    hash.insert("Emily",    'F', 2019, 300);
    hash.insert("Benjamin", 'M', 2019, 600);
    hash.insert("Benjamin", 'M', 2020, 580); // Benjamin 1180
    hash.insert("Benny",    'M', 2019, 100);
    hash.insert("Brad",     'M', 2019, 250);
    hash.insert("Brett",    'M', 2019, 90);

    return hash;
};

#endif //COP3530_PROJECT_2_TEST_HELPERS_H