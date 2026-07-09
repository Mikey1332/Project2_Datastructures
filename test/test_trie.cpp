#include "test_helper.h"

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
    REQUIRE(trie.getYearTotal("Liam", 'M', 2019, false) == 700);
    REQUIRE(trie.getYearTotal("Liam", 'M', 2020, false) == 680);
    REQUIRE(trie.getYearTotal("Liam", 'M', 2021, false) == 660);
}

TEST_CASE("Trie getYearTotal returns -1 for year not in data", "[getYearTotal][trie][year]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getYearTotal("Liam", 'M', 1800, false) == -1);
    REQUIRE(trie.getYearTotal("Liam", 'M', 2100, false) == -1);
}

TEST_CASE("Trie getYearTotal returns -1 for a name without that year", "[getYearTotal][trie][year]") {
    Trie trie = makeTestTrie();
    // Emily only has 2019
    REQUIRE(trie.getYearTotal("Emily", 'F', 2020, false) == -1);
}


// repeat my hash tests but for trie