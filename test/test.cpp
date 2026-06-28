#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "hash.h"
#include "parser.h"
#include "trie.h"

/*

trying to think of things to test: (feel free to add some)

both structures return identical results for same query (trieResult == hashResult)
upper/lower case query handling (liam Liam and LIAM return same result)
names with symbols?
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
all-time, exact, file, format, gender, gendereddata, hash, insert, prefix, range, top, trie, year

*/


Trie makeTestTrie() {
    Trie trie;

    trie.insert("Albert",   'M', 2020, 500);
    trie.insert("Albert",   'M', 2021, 700);
    trie.insert("Liam",     'M', 2019, 700);
    trie.insert("Liam",     'M', 2020, 680);
    trie.insert("Liam",     'M', 2021, 660);
    trie.insert("Bob",      'M', 2019, 600);
    trie.insert("Bob",      'M', 2020, 580);
    trie.insert("Sam",      'M', 2019, 200);
    trie.insert("Sam",      'F', 2019, 150);
    trie.insert("Emma",     'F', 2019, 500);
    trie.insert("Emma",     'F', 2020, 480);
    trie.insert("Emma",     'F', 2021, 460);
    trie.insert("Emily",    'F', 2019, 300);

    return trie;
}

// HashTable makeTestHash() {
//     HashTable hash;
//
//     hash.insert("Albert",   'M', 2020, 500);
//     hash.insert("Albert",   'M', 2021, 700);
//     hash.insert("Liam",     'M', 2019, 700);
//     hash.insert("Liam",     'M', 2020, 680);
//     hash.insert("Liam",     'M', 2021, 660);
//     hash.insert("Bob",      'M', 2019, 600);
//     hash.insert("Bob",      'M', 2020, 580);
//     hash.insert("Sam",      'M', 2019, 200);
//     hash.insert("Sam",      'F', 2019, 150);
//     hash.insert("Emma",     'F', 2019, 500);
//     hash.insert("Emma",     'F', 2020, 480);
//     hash.insert("Emma",     'F', 2021, 460);
//     hash.insert("Emily",    'F', 2019, 300);
//
//     return hash;
// }

TEST_CASE("GenderedData totals start at zero", "[gendereddata]") {
    GenderedData g;
    REQUIRE(g.getTotal('M') == 0);
    REQUIRE(g.getTotal('F') == 0);
}

TEST_CASE("GenderedData insert and getTotal accumulate correctly", "[gendereddata][insert]") {
    GenderedData g;
    g.insert('M', 2019, 500);
    g.insert('M', 2020, 300);
    REQUIRE(g.getTotal('M') == 800);
}

TEST_CASE("GenderedData male and female totals are separate", "[gendereddata]") {
    GenderedData g;
    g.insert('M', 2019, 500);
    g.insert('F', 2019, 200);
    REQUIRE(g.getTotal('M') == 500);
    REQUIRE(g.getTotal('F') == 200);
}

TEST_CASE("GenderedData getCount returns correct count for a year", "[gendereddata][year]") {
    GenderedData g;
    g.insert('F', 2019, 300);
    g.insert('F', 2020, 400);
    REQUIRE(g.getCount('F', 2019) == 300);
    REQUIRE(g.getCount('F', 2020) == 400);
}

TEST_CASE("GenderedData getCount returns zero for year not inserted", "[gendereddata][year]") {
    GenderedData g;
    g.insert('F', 2019, 300);
    REQUIRE(g.getCount('F', 1800) == 0);
    REQUIRE(g.getCount('F', 2099) == 0);
}

TEST_CASE("GenderedData getCount does not cross genders", "[gender][gendereddata]") {
    GenderedData g;
    g.insert('M', 2019, 500);
    REQUIRE(g.getCount('F', 2019) == 0);
}

TEST_CASE("Trie getTotal returns correct all-time sum", "[all-time][exact][trie]") {
    Trie trie = makeTestTrie();
    // Liam M: 700 + 680 + 660 = 2040
    REQUIRE(trie.getTotal("Liam", 'M') == 2040);
}

TEST_CASE("Trie getTotal returns zero for name not inserted", "[exact][trie]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getTotal("xyz", 'M') == 0);
}

TEST_CASE("Trie getTotal returns zero for correct name but wrong gender", "[gender][trie]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getTotal("Bob", 'F') == 0);
}

TEST_CASE("Trie getTotal M and F for same name are separate", "[gender][trie]") {
    Trie trie = makeTestTrie();
    // Sam M = 200, Sam F = 150
    REQUIRE(trie.getTotal("Sam", 'M') == 200);
    REQUIRE(trie.getTotal("Sam", 'F') == 150);
}

TEST_CASE("Trie getTotal not affected by names sharing a prefix", "[exact][trie]") {
    Trie trie = makeTestTrie();
    // Emma and Emily share "Em" but totals must be separate
    REQUIRE(trie.getTotal("Emma",  'F') == 1440); // 500+480+460
    REQUIRE(trie.getTotal("Emily", 'F') == 300);
}

TEST_CASE("Trie getYear returns correct count for a specific year", "[exact][trie][year]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getYear("Liam", 'M', 2019) == 700);
    REQUIRE(trie.getYear("Liam", 'M', 2020) == 680);
    REQUIRE(trie.getYear("Liam", 'M', 2021) == 660);
}

TEST_CASE("Trie getYear returns zero for year not in data", "[trie][year]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getYear("Liam", 'M', 1800) == 0);
    REQUIRE(trie.getYear("Liam", 'M', 2099) == 0);
}

TEST_CASE("Trie getYear returns zero for year in range but name not in that year", "[trie][year]") {
    Trie trie = makeTestTrie();
    // Emily only has 2019
    REQUIRE(trie.getYear("Emily", 'F', 2020) == 0);
}

