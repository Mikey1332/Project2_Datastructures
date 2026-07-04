#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "hash.h"
#include "parser.h"
#include "trie.h"

/*

    https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md#specifying-which-tests-to-run

    relevant flag names for consistency:
    all-time, exact, file, format, getYearTotal, gender, GenderData, hash, insert, prefix, range, top, trie, year
    [BROKEN] if doesn't work (to ignore test when running and fix later)


trying to think of things to test: (feel free to add some)

both structures return identical results for same query (trieResult == hashResult)
upper/lower case query handling (liam Liam and LIAM return same result)
names with symbols or numbers? do those exist in the SSA records? check this
time simulations
make sure total unique names accumulate correctly
    example for hash: numEntries variable == how many indexes occupied
make sure if close to hash capacity the quadratic probing wraps around

exact lookup:
exact name lookup (total)
exact name lookup (one year)

prefixes:
prefix returns correctly
single-character prefix
if prefix is longer than the name

year handling:
year range (2019-2021) sum of years

combined situations:
top 10 names that start with B in 2019

file reading tests:
lines parse correctly
multiple files load without interfering with each other
total occurrences throughout years accumulates correctly
after all files loaded, total records inserted into trie and hash should be equal

some edge cases:
name not found
year out of SSA range (1880 - 2025?)
year out of range for that name (a lot of names/spellings are new)
top-N where N is larger than actual results (top 20 names but there's only a few that match)
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
    trie.insert("Samuel",   'M', 2000, 950);
    trie.insert("Samantha", 'F', 2019, 700);
    trie.insert("Emma",     'F', 2019, 500);
    trie.insert("Emma",     'F', 2020, 480);
    trie.insert("Emma",     'F', 2021, 460);
    trie.insert("Emily",    'F', 2019, 300);

    return trie;
}

HashTable makeTestHash() {
    HashTable hash;

    hash.insert("Albert",   'M', 2020, 500);
    hash.insert("Albert",   'M', 2021, 700);
    hash.insert("Liam",     'M', 2019, 700);
    hash.insert("Liam",     'M', 2020, 680);
    hash.insert("Liam",     'M', 2021, 660);
    hash.insert("Bob",      'M', 2019, 600);
    hash.insert("Bob",      'M', 2020, 580);
    hash.insert("Sam",      'M', 2019, 200);
    hash.insert("Sam",      'F', 2019, 150);
    hash.insert("Samuel",   'M', 2000, 950);
    hash.insert("Samantha", 'F', 2019, 700);
    hash.insert("Emma",     'F', 2019, 500);
    hash.insert("Emma",     'F', 2020, 480);
    hash.insert("Emma",     'F', 2021, 460);
    hash.insert("Emily",    'F', 2019, 300);

    return hash;
}

TEST_CASE("GenderData totals start at 0", "[all-time][GenderData]") {
    GenderData g;
    REQUIRE(g.getAllTimeTotal('M') == 0);
    REQUIRE(g.getAllTimeTotal('F') == 0);
}

TEST_CASE("GenderData insert and getAllTimeTotal accumulate correctly", "[all-time][GenderData][insert]") {
    GenderData g;
    g.insert('M', 2019, 500);
    g.insert('M', 2020, 300);
    REQUIRE(g.getAllTimeTotal('M') == 800);
}

TEST_CASE("GenderData male and female totals are separate", "[all-time][GenderData]") {
    GenderData g;
    g.insert('M', 2019, 500);
    g.insert('F', 2019, 200);
    REQUIRE(g.getAllTimeTotal('M') == 500);
    REQUIRE(g.getAllTimeTotal('F') == 200);
}

TEST_CASE("GenderData getCount returns correct count for a year", "[GenderData][year]") {
    GenderData g;
    g.insert('F', 2019, 300);
    g.insert('F', 2020, 400);
    REQUIRE(g.getCount('F', 2019) == 300);
    REQUIRE(g.getCount('F', 2020) == 400);
}

TEST_CASE("GenderData getCount returns -1 for year out of bounds", "[GenderData][year]") {
    GenderData g;
    g.insert('F', 2019, 300);
    REQUIRE(g.getCount('F', 1800) == -1);
    REQUIRE(g.getCount('F', 2100) == -1);
}

TEST_CASE("GenderData getCount does not cross genders", "[gender][GenderData]") {
    GenderData g;
    g.insert('M', 2019, 500);
    g.insert('F', 2019, 100);
    REQUIRE(g.getCount('F', 2019) == 100);
}

TEST_CASE("Trie insertion does not crash", "[trie]") {
    Trie trie = makeTestTrie();
    REQUIRE(true); // Test did not crash
}

TEST_CASE("Trie getAllTimeTotal returns correct all-time sum for exact name search", "[all-time][exact][trie]") {
    Trie trie = makeTestTrie();
    // Liam M: 700 + 680 + 660 = 2040
    REQUIRE(trie.getAllTimeTotal("Liam", 'M', false) == 2040);
}

TEST_CASE("Trie getAllTimeTotal for name not inserted for exact name search", "[all-time][exact][trie][BROKEN]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getAllTimeTotal("xyz", 'M', false) == 0);
}

TEST_CASE("Trie getAllTimeTotal for correct name but wrong gender for exact search", "[all-time][exact][gender][trie][BROKEN]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getAllTimeTotal("Bob", 'F', false) == 0);
}

TEST_CASE("Trie getAllTimeTotal M and F for same name are separate for exact name search", "[all-time][exact][gender][trie]") {
    Trie trie = makeTestTrie();
    // Sam M = 200, Sam F = 150
    REQUIRE(trie.getAllTimeTotal("Sam", 'M', false) == 200);
    REQUIRE(trie.getAllTimeTotal("Sam", 'F', false) == 150);
}

TEST_CASE("Trie getAllTimeTotal exact searches not affected by names sharing a prefix", "[all-time][exact][trie]") {
    Trie trie = makeTestTrie();
    // Emma and Emily share "Em" but totals must be separate
    REQUIRE(trie.getAllTimeTotal("Emma",  'F', false) == 1440); // 500+480+460
    REQUIRE(trie.getAllTimeTotal("Emily", 'F', false) == 300);
}

TEST_CASE("Trie getYearTotal returns correct count for a specific year", "[exact][getYearTotal][trie][year]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getYearTotal("Liam", 'M', 2019) == 700);
    REQUIRE(trie.getYearTotal("Liam", 'M', 2020) == 680);
    REQUIRE(trie.getYearTotal("Liam", 'M', 2021) == 660);
}

TEST_CASE("Trie getYearTotal returns -1 for year not in data", "[getYearTotal][trie][year]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getYearTotal("Liam", 'M', 1800) == -1);
    REQUIRE(trie.getYearTotal("Liam", 'M', 2100) == -1);
}

TEST_CASE("Trie getYearTotal returns -1 for a name without that year", "[getYearTotal][trie][year]") {
    Trie trie = makeTestTrie();
    // Emily only has 2019
    REQUIRE(trie.getYearTotal("Emily", 'F', 2020) == -1);
}

TEST_CASE("Hash function hashes correctly", "[hash][BROKEN]") {
    HashTable hash;

    string name1 = "A";
    string name2 = "Ba";
    string name3 = "Cat";
    string name4 = "Dolly";
    string name5 = "Verylongname";
    string name6 = "Zzzzzzzzzzzz"; // should be large number before getting mod

    REQUIRE(hash.hash(name6) == 0); // should be FALSE for now until i make better hash
    REQUIRE(hash.hash(name2) == 0);
    REQUIRE(hash.hash(name3) == 0);
    REQUIRE(hash.hash(name4) == 0);
    REQUIRE(hash.hash(name5) == 0);
    REQUIRE(hash.hash(name1) == 0);
}

TEST_CASE("Insert one line into hash table", "[hash]") {
    HashTable hash;
    string name = "Albert";
    char sex = 'M';
    int year = 2020;
    int count = 500;

    REQUIRE(hash.getFilledSlots() == 0); // Not inserted yet = 0

    hash.insert(name, sex, year, count);

    REQUIRE(hash.getFilledSlots() == 1); // Filled Slots updated
    REQUIRE(hash.getAllTimeTotal(name,sex,false) == 500);
}

TEST_CASE("Hash filledSlots matches manually calculated occupied slots","[hash]") {
    HashTable hash = makeTestHash();
    int occupied = 0;
    for (int i = 0; i < hash.getCapacity(); i++) {
        if (hash.getOccupied(i)) {
            occupied++;
        }
    }
    // Warning: this will fail if the test hash tree is modified
    REQUIRE(hash.getFilledSlots() == 8);
    REQUIRE(occupied == 8);
}

TEST_CASE("Hash getAllTimeTotal returns correct all-time sum for exact name search", "[all-time][exact][hash]") {
    HashTable hash = makeTestHash();
    // Liam M: 700 + 680 + 660 = 2040
    REQUIRE(hash.getAllTimeTotal("Liam", 'M', false) == 2040);
}

TEST_CASE("Hash getAllTimeTotal for name not inserted for exact name search", "[all-time][exact][hash]") {
    HashTable hash = makeTestHash();
    REQUIRE(hash.getAllTimeTotal("xyz", 'M', false) == 0);
}

TEST_CASE("Hash getAllTimeTotal for correct name but wrong gender for exact search", "[all-time][exact][gender][hash]") {
    HashTable hash = makeTestHash();
    REQUIRE(hash.getAllTimeTotal("Bob", 'F', false) == 0);
}

TEST_CASE("Hash getAllTimeTotal M and F for same name are separate for exact name search", "[all-time][exact][gender][hash]") {
    HashTable hash = makeTestHash();
    // Sam M = 200, Sam F = 150, ignores Samuel and Samantha
    REQUIRE(hash.getAllTimeTotal("Sam", 'M', false) == 200);
    REQUIRE(hash.getAllTimeTotal("Sam", 'F', false) == 150);
}

TEST_CASE("Hash getAllTimeTotal exact searches not affected by names sharing a prefix", "[all-time][exact][hash]") {
    HashTable hash = makeTestHash();
    // Emma and Emily share "Em" but totals must be separate
    REQUIRE(hash.getAllTimeTotal("Emma",  'F', false) == 1440); // 500+480+460
    REQUIRE(hash.getAllTimeTotal("Emily", 'F', false) == 300);
}

TEST_CASE("Hash getYearTotal returns correct count for a specific year", "[exact][getYearTotal][hash][year]") {
    HashTable hash = makeTestHash();
    REQUIRE(hash.getYearTotal("Liam", 'M', 2019) == 700);
    REQUIRE(hash.getYearTotal("Liam", 'M', 2020) == 680);
    REQUIRE(hash.getYearTotal("Liam", 'M', 2021) == 660);
}

TEST_CASE("Hash getYearTotal returns -1 for year not in data", "[getYearTotal][hash][year]") {
    HashTable hash = makeTestHash();
    REQUIRE(hash.getYearTotal("Liam", 'M', 1800) == -1);
    REQUIRE(hash.getYearTotal("Liam", 'M', 2099) == -1);
}

TEST_CASE("Hash getYearTotal returns -1 for a name without that year", "[getYearTotal][hash][year]") {
    HashTable hash = makeTestHash();
    // Emily only has 2019
    REQUIRE(hash.getYearTotal("Emily", 'F', 2020) == -1);
}

TEST_CASE("Hash getAllTimeTotal returns correct all-time sum for prefix search", "[all-time][hash][prefix]") {
    HashTable hash = makeTestHash();
    // Emma F: 500+480+460
    // Emily F: 300
    // Total "Em" = 1740
    REQUIRE(hash.getAllTimeTotal("Em", 'F', true) == 1740);
}

TEST_CASE("Hash getAllTimeTotal for name not inserted for prefix search", "[all-time][hash][prefix]") {
    HashTable hash = makeTestHash();
    REQUIRE(hash.getAllTimeTotal("xyz", 'M', true) == 0);
}

TEST_CASE("Hash getAllTimeTotal M and F for same name are separate for prefix search", "[all-time][gender][hash][prefix]") {
    HashTable hash = makeTestHash();
    // M : Sam + Samuel = 200+950
    // F : Sam + Samantha = 150+700
    REQUIRE(hash.getAllTimeTotal("Sam", 'M', true) == 1150);
    REQUIRE(hash.getAllTimeTotal("Sam", 'F', true) == 850);
}