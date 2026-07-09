#include "test_helper.h"

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
    REQUIRE(hash.getYearTotal("Liam", 'M', 2019, false) == 700);
    REQUIRE(hash.getYearTotal("Liam", 'M', 2020, false) == 680);
    REQUIRE(hash.getYearTotal("Liam", 'M', 2021, false) == 660);
}

TEST_CASE("Hash getYearTotal returns -1 for year not in data", "[getYearTotal][hash][year]") {
    HashTable hash = makeTestHash();
    REQUIRE(hash.getYearTotal("Liam", 'M', 1800, false) == -1);
    REQUIRE(hash.getYearTotal("Liam", 'M', 2099, false) == -1);
}

TEST_CASE("Hash getYearTotal returns -1 for a name without that year", "[getYearTotal][hash][year]") {
    HashTable hash = makeTestHash();
    // Emily only has 2019
    REQUIRE(hash.getYearTotal("Emily", 'F', 2020, false) == -1);
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

// // fix stuff
//
// TEST_CASE("Hash topN returns correct number of results", "[hash][prefix][topN][BROKEN]") {
//     HashTable hash = makeTestHash();
//     auto results = hash.topN("B", 'M', 3,true); // random num fix later
//     REQUIRE(results.size() == 3);
// }
//
// TEST_CASE("Hash topN results are sorted descending by count", "[hash][prefix][topN][BROKEN]") {
//     HashTable hash = makeTestHash();
//     auto results = hash.topN("B", 'M', 3,true);
//     for (int i = 0; i < (int)results.size() - 1; i++)
//         REQUIRE(results[i].second >= results[i+1].second);
// }
//
// TEST_CASE("Hash topN returns correct top 3 names", "[hash][prefix][topN][BROKEN]") {
//     HashTable hash = makeTestHash();
//     auto results = hash.topN("B", 'M', 3,true);
//     REQUIRE(results[0].first == "Benjamin");
//     REQUIRE(results[0].second == 1180);
//     REQUIRE(results[1].first == "Bob");
//     REQUIRE(results[1].second == 400);
//     REQUIRE(results[2].first == "Brad");
//     REQUIRE(results[2].second == 250);
// }
//
// TEST_CASE("Hash topN does not include wrong gender", "[gender][hash][prefix][topN][BROKEN]") {
//     HashTable hash = makeTestHash();
//     auto results = hash.topN("B", 'M', 5,true);
//     for (auto result : results)
//         REQUIRE(result.first != "Alice");
// }
//
// TEST_CASE("Hash topN, N more than actual results, returns only results", "[edge][hash][prefix][topN][BROKEN]") {
//     HashTable hash = makeTestHash();
//     auto results = hash.topN("B", 'M', 20,true);
//     REQUIRE(results.size() == 5);
// }
//
// TEST_CASE("Hash topN with no matching prefix returns empty", "[edge][hash][prefix][topN][BROKEN]") {
//     HashTable hash = makeTestHash();
//     auto results = hash.topN("Qzx", 'M', 10,true);
//     REQUIRE(results.empty());
// }
//
// TEST_CASE("Hash topN with N=1 returns only the single highest", "[hash][prefix][topN][BROKEN]") {
//     HashTable hash = makeTestHash();
//     auto results = hash.topN("B", 'M', 1,true);
//     REQUIRE(results.size() == 1);
//     REQUIRE(results[0].first == "Benjamin");
//     REQUIRE(results[0].second == 1180);
// }
//
// TEST_CASE("Hash topN counts reflect all-time totals not single year", "[all-time][hash][prefix][topN][BROKEN]") {
//     HashTable hash = makeTestHash();
//     auto results = hash.topN("B", 'M', 1,true);
//     REQUIRE(results[0].second == 1180);
// }
//
// // do same for name full name not prefix