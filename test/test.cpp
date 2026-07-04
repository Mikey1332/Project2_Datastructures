#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "hash.h"
#include "parser.h"
#include "trie.h"

/*

trying to think of things to test: (feel free to add some)

both structures return identical results for same query (trieResult == hashResult)
upper/lower case query handling (liam Liam and LIAM return same result)
names with symbols or numbers? do those exist in the SSA records?
time simulations

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
all-time, exact, file, format, gender, GenderData, hash, insert, prefix, range, top, trie, year

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

// TEST_CASE("GenderData totals start at zero", "[GenderData]") {
//     GenderData g;
//     REQUIRE(g.getAllTimeTotal('M') == 0);
//     REQUIRE(g.getAllTimeTotal('F') == 0);
// }
//
// TEST_CASE("GenderData insert and getAllTimeTotal accumulate correctly", "[GenderData][insert]") {
//     GenderData g;
//     g.insert('M', 2019, 500);
//     g.insert('M', 2020, 300);
//     REQUIRE(g.getAllTimeTotal('M') == 800);
// }
//
// TEST_CASE("GenderData male and female totals are separate", "[GenderData]") {
//     GenderData g;
//     g.insert('M', 2019, 500);
//     g.insert('F', 2019, 200);
//     REQUIRE(g.getAllTimeTotal('M') == 500);
//     REQUIRE(g.getAllTimeTotal('F') == 200);
// }
//
// TEST_CASE("GenderData getCount returns correct count for a year", "[GenderData][year]") {
//     GenderData g;
//     g.insert('F', 2019, 300);
//     g.insert('F', 2020, 400);
//     REQUIRE(g.getCount('F', 2019) == 300);
//     REQUIRE(g.getCount('F', 2020) == 400);
// }
//
// TEST_CASE("GenderData getCount returns -1 for year out of bounds", "[GenderData][year]") {
//     GenderData g;
//     g.insert('F', 2019, 300);
//     REQUIRE(g.getCount('F', 1800) == -1);
//     REQUIRE(g.getCount('F', 2100) == -1);
// }
//
// TEST_CASE("GenderData getCount does not cross genders", "[gender][GenderData]") {
//     GenderData g;
//     g.insert('M', 2019, 500);
//     g.insert('F', 2019, 100);
//     REQUIRE(g.getCount('F', 2019) == 100);
// }
//
// TEST_CASE("Trie getAllTimeTotal returns correct all-time sum", "[all-time][exact][trie]") {
//     Trie trie = makeTestTrie();
//     // Liam M: 700 + 680 + 660 = 2040
//     REQUIRE(trie.getAllTimeTotal("Liam", 'M') == 2040);
// }
//
// TEST_CASE("Trie getAllTimeTotal returns zero for name not inserted", "[exact][trie]") {
//     Trie trie = makeTestTrie();
//     REQUIRE(trie.getAllTimeTotal("xyz", 'M') == 0);
// }
//
// TEST_CASE("Trie getAllTimeTotal returns zero for correct name but wrong gender", "[gender][trie]") {
//     Trie trie = makeTestTrie();
//     REQUIRE(trie.getAllTimeTotal("Bob", 'F') == 0);
// }
//
// TEST_CASE("Trie getAllTimeTotal M and F for same name are separate", "[gender][trie]") {
//     Trie trie = makeTestTrie();
//     // Sam M = 200, Sam F = 150
//     REQUIRE(trie.getAllTimeTotal("Sam", 'M') == 200);
//     REQUIRE(trie.getAllTimeTotal("Sam", 'F') == 150);
// }
//
// TEST_CASE("Trie getAllTimeTotal not affected by names sharing a prefix", "[exact][trie]") {
//     Trie trie = makeTestTrie();
//     // Emma and Emily share "Em" but totals must be separate
//     REQUIRE(trie.getAllTimeTotal("Emma",  'F') == 1440); // 500+480+460
//     REQUIRE(trie.getAllTimeTotal("Emily", 'F') == 300);
// }
//
// TEST_CASE("Trie getYearTotal returns correct count for a specific year", "[exact][trie][year]") {
//     Trie trie = makeTestTrie();
//     REQUIRE(trie.getYearTotal("Liam", 'M', 2019) == 700);
//     REQUIRE(trie.getYearTotal("Liam", 'M', 2020) == 680);
//     REQUIRE(trie.getYearTotal("Liam", 'M', 2021) == 660);
// }
//
// TEST_CASE("Trie getYearTotal returns zero for year not in data", "[trie][year]") {
//     Trie trie = makeTestTrie();
//     REQUIRE(trie.getYearTotal("Liam", 'M', 1800) == 0);
//     REQUIRE(trie.getYearTotal("Liam", 'M', 2099) == 0);
// }
//
// TEST_CASE("Trie getYearTotal returns zero for a name without that year", "[trie][year]") {
//     Trie trie = makeTestTrie();
//     // Emily only has 2019
//     REQUIRE(trie.getYearTotal("Emily", 'F', 2020) == 0);
// }

TEST_CASE("Hash function hashes correctly", "[hash]") {
    HashTable hash;
    string name = "abc";
    REQUIRE(hash.hash(name) == 0); // should be false for now
}