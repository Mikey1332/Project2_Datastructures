#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "hash.h"
#include "parser.h"
#include "trie.h"

/*

trying to think of things to test: (feel free to add some)

both structures return identical results for same query (trieResult == hashResult)
upper/lower case query handling (liam Liam and LIAM return same result)
gender variation (m sam vs f sam)

exact lookup:
exact name lookup (total)
exact name lookup (one year)

prefixes:
prefix returns correctly
single-character prefix

year handling:
year range (2019-2021) sum of years

combined situations:
top 10 names that start with B in 2019

file reading tests:
lines parse correctly
multiple files load without interfering with each other
total occurrences throughout years accumulates correctly
after all files loaded, total records inserted into trie and hash should be equal

edge cases:
name not found
year out of range (I think 1880? and 2025? I'll check the ssa files later)
year out of range for that name (a lot of names/spellings are new)
top-N where N is larger than actual results (top 20 names but there's only a few that match)

relevant flag names for consistency:
exact, prefix, year, edge, top, trie, hash, gender, format, file, range

*/


void insertTestData(Trie& trie, HashTable& hash) {
    // call this in tests, that way tests don't rely on reading real files
    // (unless the test is to read files of course)

    trie.insert("Albert",   'M', 2020, 500);
    trie.insert("Albert",   'M', 2021, 700);

    hash.insert("Albert",   'M', 2020, 500);
    hash.insert("Albert",   'M', 2021, 700);
    // add a lot more
}


TEST_CASE("Exact name search returns correct all time total", "[exact][trie][hash]") {
    Trie trie;
    HashTable hash;
    insertTestData(trie, hash);
    // Albert (M) total: 500 + 700 = 1200
    REQUIRE(trie.getTotal("Albert", 'M') == 1200);
    REQUIRE(hash.getTotal("Albert", 'M') == 1200);
}

TEST_CASE("Exact name search for a single year returns correct count", "[exact][year][trie][hash]") {
    Trie trie; HashTable hash;
    insertTestData(trie, hash);
    REQUIRE(trie.getYear("Albert", 'M', 2021) == 700);
    REQUIRE(hash.getYear("Albert", 'M', 2021) == 700);
}