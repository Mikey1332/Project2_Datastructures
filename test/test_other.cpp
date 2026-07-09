#include "test_helper.h"

/*

    https://github.com/catchorg/Catch2/blob/devel/docs/command-line.md#specifying-which-tests-to-run

    relevant flag names for consistency:
    all-time, exact, file, format, getYearTotal, gender, GenderData, hash, insert, prefix, range, topN, trie, year
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

// probably file reading, and anything that combines trie and hash