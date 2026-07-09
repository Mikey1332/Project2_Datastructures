#include "test_helper.h"

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