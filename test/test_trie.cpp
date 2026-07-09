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

TEST_CASE("Trie getAllTimeTotal for name not inserted for exact name search", "[all-time][exact][trie]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getAllTimeTotal("xyz", 'M', false) == 0);
}

TEST_CASE("Trie getAllTimeTotal for correct name but wrong gender for exact search", "[all-time][exact][gender][trie]") {
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

TEST_CASE("Trie getYearTotal returns 0 for year not in data", "[getYearTotal][trie][year]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getYearTotal("Liam", 'M', 1800, false) == 0);
    REQUIRE(trie.getYearTotal("Liam", 'M', 2100, false) == 0);
}

TEST_CASE("Trie getYearTotal returns 0 for a name without that year", "[getYearTotal][trie][year]") {
    Trie trie = makeTestTrie();
    // Emily only has 2019
    REQUIRE(trie.getYearTotal("Emily", 'F', 2020, false) == 0);
}

TEST_CASE("Trie getAllTimeTotal returns correct all-time sum for prefix search", "[all-time][trie][prefix]") {
    Trie trie = makeTestTrie();
    // Emma F: 500 + 480 + 460
    // Emily F: 300
    // Total "Em" = 1740
    REQUIRE(trie.getAllTimeTotal("Em", 'F', true) == 1740);
}

TEST_CASE("Trie getAllTimeTotal for name not inserted for prefix search", "[all-time][trie][prefix]") {
    Trie trie = makeTestTrie();
    REQUIRE(trie.getAllTimeTotal("xyz", 'M', true) == 0);
}

TEST_CASE("Trie getAllTimeTotal M and F for same name are separate for prefix search", "[all-time][gender][trie][prefix]") {
    Trie trie = makeTestTrie();
    // M : Sam + Samuel = 200 + 950
    // F : Sam + Samantha = 150 + 700
    REQUIRE(trie.getAllTimeTotal("Sam", 'M', true) == 1150);
    REQUIRE(trie.getAllTimeTotal("Sam", 'F', true) == 850);
}

TEST_CASE("Trie topN returns correct number of results", "[trie][topN]") {
    Trie trie = makeTestTrie();
    auto results = trie.topN("B", 'M', 3);
    REQUIRE(results.size() == 3);
}

TEST_CASE("Trie topN results are sorted descending by count", "[trie][topN]") {
    Trie trie = makeTestTrie();
    auto results = trie.topN("B", 'M', 3);

    for (int i = 0; i < (int)results.size() - 1; i++)
        REQUIRE(results[i].second >= results[i + 1].second);
}

TEST_CASE("Trie topN returns correct top 3 names", "[trie][topN]") {
    Trie trie = makeTestTrie();
    auto results = trie.topN("B", 'M', 3);
    REQUIRE(results[0].first == "Bob");
    REQUIRE(results[0].second == 1180);
    REQUIRE(results[1].first == "Benjamin");
    REQUIRE(results[1].second == 1180);
    REQUIRE(results[2].first == "Brad");
    REQUIRE(results[2].second == 250);
}

TEST_CASE("Trie topN filters by gender", "[gender][trie][topN]") {
    Trie trie = makeTestTrie();
    vector<pair<string,int>> results;

    SECTION("Male only") {
        results = trie.topN("Sam", 'M', 5);

        REQUIRE(results.size() == 2); // Sam and Samuel
        REQUIRE(results[0].first == "Samuel"); // 950
        REQUIRE(results[1].first == "Sam"); // 200

        bool foundSamantha = false;
        for (const auto& result : results)
            if (result.first == "Samantha")
                foundSamantha = true;

        REQUIRE_FALSE(foundSamantha);
    }

    SECTION("Female only") {
        results = trie.topN("Sam", 'F', 5);

        REQUIRE(results.size() == 2); // Sam and Samantha
        REQUIRE(results[0].first == "Samantha"); // 700
        REQUIRE(results[1].first == "Sam"); // 150

        bool foundSamuel = false;
        for (const auto& result : results)
            if (result.first == "Samuel")
                foundSamuel = true;

        REQUIRE_FALSE(foundSamuel);
    }

    SECTION("All genders") {
        results = trie.topN("Sam", 'A', 5);

        REQUIRE(results.size() == 3); // Sam Samuel Samantha

        bool foundSamuel = false;
        for (const auto& result : results)
            if (result.first == "Samuel")
                foundSamuel = true;
        REQUIRE(foundSamuel);

        bool foundSamantha = false;
        for (const auto& result : results)
            if (result.first == "Samuel")
                foundSamantha = true;
        REQUIRE(foundSamantha);

        bool foundSam = false;
        for (const auto& result : results)
            if (result.first == "Samuel")
                foundSam = true;
        REQUIRE(foundSam);
    }
}

TEST_CASE("Trie topN, N more than actual results, returns only results", "[trie][topN]") {
    Trie trie = makeTestTrie();
    auto results = trie.topN("B", 'M', 20);
    // 5 names start with B
    REQUIRE(results.size() == 5);
}

TEST_CASE("Trie topN with no matching prefix returns empty", "[trie][topN]") {
    Trie trie = makeTestTrie();
    auto results = trie.topN("Qzx", 'M', 10);
    REQUIRE(results.empty());
}

TEST_CASE("Trie topN with N=1 returns only the single highest", "[trie][topN]") {
    Trie trie = makeTestTrie();
    auto results = trie.topN("B", 'M', 1);
    REQUIRE(results.size() == 1);
    REQUIRE(results[0].first == "Bob");
    REQUIRE(results[0].second == 1180);
}

// wait was topN supposed to filter by year?

// TEST_CASE("Trie topN counts reflect all-time totals not single year", "[all-time][trie][topN]") {
//     Trie trie = makeTestTrie();
//     auto results = trie.topN("B", 'M', 1);
//     REQUIRE(results[0].second == 1180);
// }