#include <iostream>
#include <iomanip>
#include "trie.h"
#include "hash.h"
#include "load.h"
#include <chrono>
using namespace std;

void printMenu() {
	cout << "================ Baby Name Search Menu ================\n"
		"0. Reprint Menu\n"
		"1. Name - total births (all-time)\n" //name, sex
		"2. Name - births in a specific year\n" //name, year, sex
		"3. Name - births across a year range\n" //name year1, year2, sex
		"4. Name - year-by-year trend\n" //name, sex
		"5. Prefix - total births (all-time, combined)\n" //prefix, sex
		"6. Prefix - matches in a specific year\n" //prefix, year, sex
		"7. Prefix - matches across a year range\n" //prefix, year1, year2, sex
		"8. Prefix - year-by-year trend (combined)\n" //prefix, sex
		"9. Prefix - top N names (sex/year filter)\n" //prefix, sex, year, N
		"10. Run performance benchmark\n"
		"11. Quit" << endl;
}

long long findAverage(vector<long long> nums) {
	if (nums.empty())
		return 0;
	long long sum = 0;
	for (int i = 0; i < (int)nums.size(); i++) {
		sum += nums[i];
	}
	return sum/nums.size();
}

int main(){
	Trie trie;
	HashTable hash;
	string line, name, selectionString;
	char sex = ' ';
	bool running = true;
	int selection = -1;
	int year = -1;
	int year2 = -1;
	int N = -1;

	//Time Storage
	auto start = chrono::high_resolution_clock::now();
	auto end = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
	long long trieInsertTime;
	long long hashInsertTime;
	vector<long long> trieAllTimeBirthTimes;
	vector<long long> hashAllTimeBirthTimes;
	vector<long long> trieYearBirthTimes;
	vector<long long> hashYearBirthTimes;
	vector<long long> trieYearRangeBirthTimes;
	vector<long long> hashYearRangeBirthTimes;
	vector<long long> trieYearByYearBirthTimes;
	vector<long long> hashYearByYearBirthTimes;
	vector<long long> trieAllTimeBirthTimesPrefix;
	vector<long long> hashAllTimeBirthTimesPrefix;
	vector<long long> trieYearBirthTimesPrefix;
	vector<long long> hashYearBirthTimesPrefix;
	vector<long long> trieYearRangeBirthTimesPrefix;
	vector<long long> hashYearRangeBirthTimesPrefix;
	vector<long long> trieYearByYearBirthTimesPrefix;
	vector<long long> hashYearByYearBirthTimesPrefix;
	vector<long long> trieTopNTimes;
	vector<long long> hashTopNTimes;

	cout << "Loading Data..." << endl;
	cout << "0%" << endl;

	//Do File Parsing:
	Parser parser;

	cout << "20%" << endl;

	//Trie:
	start = chrono::high_resolution_clock::now();
	parser.insertTrie(trie);
	end = chrono::high_resolution_clock::now();
	cout << "40%" << endl;
	trieInsertTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

	cout << "60%" << endl;

	//Hash:
	start = chrono::high_resolution_clock::now();
	parser.insertHash(hash);
	end = chrono::high_resolution_clock::now();
	cout << "80%" << endl;
	hashInsertTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

	cout << "100%\n" << endl;

	//User Selection
	printMenu();

	while (running) {
		selection = -1;
		sex = ' ';
		year = -1;
		year2 = -1;
		N = -1;

		while (selection == -1) {
			line.clear();
			cout << "\nPlease enter your selection (#0-11): ";
			getline(cin, line);
			try {
				selection = stoi(line);
			}
			catch (exception& e) {
				cout << "Please enter a valid number." << endl;
			}
			if (selection < 0 || selection > 11) {
				cout << "Please enter a number between 0 and 11." << endl;
				selection = -1;
			}
		}

		//Name/Prefix Insert:
		if (selection != 0 && selection != 10 && selection != 11) {
			name.clear();
			cout << "Please enter the name/prefix: ";
			getline(cin, name);
		}

		//Specific Year Selection
		if (selection == 2 || selection == 6 || selection == 9) {
			while (year == -1) {
				line.clear();
				cout << "Please enter the year";
				if (selection == 9)
					cout << " or \"N\" to skip";
				cout << ": ";
				getline(cin, line);
				if (line == "N")
					break;
				try {
					year = stoi(line);
				}
				catch (exception& e) {
					cout << "Please enter a valid number." << endl;
				}
			}
		}
		//Year Range Selection
		else if (selection == 3 || selection == 7) {
			while (year == -1) {
				line.clear();
				cout << "Please enter the starting year: ";
				getline(cin, line);
				try {
					year = stoi(line);
				}
				catch (exception& e) {
					cout << "Please enter a valid number." << endl;
				}
			}
			while (year2 == -1) {
				line.clear();
				cout << "Please enter the ending year: ";
				getline(cin, line);
				try {
					year2 = stoi(line);
				}
				catch (exception& e) {
					cout << "Please enter a valid number." << endl;
				}
			}
		}
		//Sex Selection
		if (selection != 0 && selection != 10 && selection != 11) {
			while (sex == ' ') {
				line.clear();
				cout << "Please enter the sex (A = All, M = Male, F = Female): ";
				getline(cin, line);
				if (line.size() > 1 || line.empty()) {
					cout << "Please enter one letter (A/M/F)." << endl;
					sex = ' ';
				}
				else
					sex = toupper(line[0]);
				if (sex != 'A' && sex != 'M' && sex != 'F') {
					cout << "Please enter one of these letter (A/M/F)." << endl;
					sex = ' ';
				}
			}
		}
		if (selection == 9) {
			//N Selection
			while (N == -1) {
				line.clear();
				cout << "Please enter the top number of names to display (#): ";
				getline(cin, line);
				try {
					N = stoi(line);
				}
				catch (exception& e) {
					cout << "Please enter a valid number." << endl;
				}
				if (N < 1 || N > 100) {
					cout << "Please enter a number between 1 and 100." << endl;
					N = -1;
				}
			}
		}

		cout << endl;

		if (selection == 0) {
			printMenu();
		}
		else if (selection == 1) {
			// cout << "You chose total births of \"" << name << "\" (" << sex << ") for all time." << endl;
			int allTimeTotal;

			start = chrono::high_resolution_clock::now();
			allTimeTotal = trie.getAllTimeTotal(name, sex, false);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Trie ----------------" << endl;
			cout << "There are [" << allTimeTotal << "] births for \"" << name << "\" (" << sex << ") for all time." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			trieAllTimeBirthTimes.push_back(elapsed.count());

			start = chrono::high_resolution_clock::now();
			allTimeTotal = hash.getAllTimeTotal(name, sex, false);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Hash ----------------" << endl;
			cout << "There are [" << allTimeTotal << "] births for \"" << name << "\" (" << sex << ") for all time." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			hashAllTimeBirthTimes.push_back(elapsed.count());
		}
		else if (selection == 2) {
			// cout << "You chose total births of \"" << name << "\" (" << sex << ") in " << year << "." << endl;
			int yearTotal;

			start = chrono::high_resolution_clock::now();
			yearTotal = trie.getYearTotal(name, sex, year, false);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Trie ----------------" << endl;
			cout << "There are [" << yearTotal << "] births for \"" << name << "\" (" << sex << ") in " << year << "." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			trieYearBirthTimes.push_back(elapsed.count());

			start = chrono::high_resolution_clock::now();
			yearTotal = hash.getYearTotal(name, sex, year, false);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Hash ----------------" << endl;
			cout << "There are [" << yearTotal << "] births for \"" << name << "\" (" << sex << ") in " << year << "." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			hashYearBirthTimes.push_back(elapsed.count());

		}
		else if (selection == 3) {
			// cout << "You chose total births of \"" << name << "\" (" << sex << ") from " << year << " to " << year2 << "." << endl;

			int total = 0;
			start = chrono::high_resolution_clock::now();
			for (int y = year; y <= year2; y++) {
				total += trie.getYearTotal(name, sex, y, false);
			}
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
			trieYearRangeBirthTimes.push_back(elapsed.count());

			cout << "---------------- Trie ----------------" << endl;
			cout << "There are [" << total << "] births for \"" << name << "\"  (" << sex << ") from " << year << " to " << year2 << "." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			total = 0;
			start = chrono::high_resolution_clock::now();
			for (int y = year; y <= year2; y++) {
				total += hash.getYearTotal(name, sex, y, false);
			}
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Hash ----------------" << endl;
			cout << "There are [" << total << "] births for \"" << name << "\"  (" << sex << ") from " << year << " to " << year2 << "." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			hashYearRangeBirthTimes.push_back(elapsed.count());
		}
		else if (selection == 4) {
			cout << "You chose the year-by-year trend of \"" << name << "\" (" << sex << ")." << endl;
		}
		else if (selection == 5) {
			// cout << "You chose total births of prefix \"" << name << "-\" (" << sex << ") for all time." << endl;
			int allTimeTotal = 0;

			start = chrono::high_resolution_clock::now();
			allTimeTotal = trie.getAllTimeTotal(name, sex, true);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Trie ----------------" << endl;
			cout << "There are [" << allTimeTotal << "] births of prefix \"" << name << "-\" (" << sex << ") for all time." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			trieAllTimeBirthTimesPrefix.push_back(elapsed.count());

			allTimeTotal = 0;

			start = chrono::high_resolution_clock::now();
			allTimeTotal = hash.getAllTimeTotal(name, sex, true);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Hash ----------------" << endl;
			cout << "There are [" << allTimeTotal << "] births of prefix \"" << name << "-\" (" << sex << ") for all time." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			hashAllTimeBirthTimesPrefix.push_back(elapsed.count());
		}
		else if (selection == 6) {
			// cout << "You chose total births of prefix \"" << name << "-\" (" << sex << ") in " << year << "." << endl;
			int yearTotal = 0;

			start = chrono::high_resolution_clock::now();
			yearTotal = trie.getYearTotal(name, sex, year, true);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Trie ----------------" << endl;
			cout << "There are [" << yearTotal << "] births of prefix \"" << name << "-\" (" << sex << ") in " << year << "." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			trieYearBirthTimesPrefix.push_back(elapsed.count());

			yearTotal = 0;

			start = chrono::high_resolution_clock::now();
			yearTotal = hash.getYearTotal(name, sex, year, true);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Hash ----------------" << endl;
			cout << "There are [" << yearTotal << "] births of prefix \"" << name << "-\" (" << sex << ") in " << year << "." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			hashYearBirthTimesPrefix.push_back(elapsed.count());

		}
		else if (selection == 7) {
			// cout << "You chose total births of prefix \"" << name << "-\" (" << sex << ") from " << year << " to " << year2 << "." << endl;

			int total = 0;
			start = chrono::high_resolution_clock::now();
			for (int y = year; y <= year2; y++) {
				total += trie.getYearTotal(name, sex, y, true);
			}
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Trie ----------------" << endl;
			cout << "There are [" << total << "] births of prefix \"" << name << "-\"  (" << sex << ") from " << year << " to " << year2 << "." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			trieYearRangeBirthTimesPrefix.push_back(elapsed.count());

			total = 0;

			start = chrono::high_resolution_clock::now();
			for (int y = year; y <= year2; y++) {
				total += hash.getYearTotal(name, sex, y, true);
			}
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Hash ----------------" << endl;
			// cout << "There are [" << total << "] births of prefix \"" << name << "-\"  (" << sex << ") from " << year << " to " << year2 << "." << endl;
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			hashYearRangeBirthTimesPrefix.push_back(elapsed.count());
		}
		else if (selection == 8) {
			cout << "You chose the year-by-year trend of prefix \"" << name << "-\" (" << sex << ")." << endl;
		}
		else if (selection == 9) {
			// cout << "You chose the top " << N << " names for prefix \"" << name << "-\" (" << sex << ")";
			// if (year != -1)
			// 	cout << " in " << year;
			// cout << "." << endl;

			vector<pair<string, int>> topN;

			start = chrono::high_resolution_clock::now();
			topN = trie.topN(name, sex, N);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Trie ----------------" << endl;
			cout << "The top " << N << " names for prefix \"" << name << "-\" (" << sex << ") are as follows:" << endl;
			for (int i = 0; i < topN.size(); i++) {
				cout << i+1 << ". " << topN[i].first << " " << topN[i].second << endl;
			}
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			trieTopNTimes.push_back(elapsed.count());

			topN.clear();

			start = chrono::high_resolution_clock::now();
			topN = hash.topN(name, sex, N);
			end = chrono::high_resolution_clock::now();
			elapsed = chrono::duration_cast<chrono::microseconds>(end - start);

			cout << "---------------- Hash ----------------" << endl;
			cout << "The top " << N << " names for prefix \"" << name << "-\" (" << sex << ") are as follows:" << endl;
			for (int i = 0; i < topN.size(); i++) {
				cout << i+1 << ". " << topN[i].first << " " << topN[i].second << endl;
			}
			cout << "Time: " << elapsed.count() << " microseconds" << endl;
			cout << endl;

			hashTopNTimes.push_back(elapsed.count());

		}
		else if (selection == 10) {
			long long trieTime = 0;
			long long hashTime = 0;
			long long trieSum = 0;
			long long hashSum = 0;

			cout << "================ Performance Benchmark ================\n" << endl;

			cout << left
				 << setw(45) << "Operation"
				 << setw(15) << "Trie (µs)"
				 << setw(15) << "Hash Table (µs)" << endl;

			cout << "---------------------------------------------------------------------------" << endl;

			cout << setw(45) << "Insert"
				 << setw(15) << trieInsertTime
				 << setw(15) << hashInsertTime << endl;

			cout << "---------------------------------------------------------------------------" << endl;

			trieTime = findAverage(trieAllTimeBirthTimes);
			hashTime = findAverage(hashAllTimeBirthTimes);
			trieSum += trieTime;
			hashSum += hashTime;
			cout << setw(45) << "All-Time Birth Search (avg.)"
				 << setw(15) << (trieTime == 0 ? "----" : to_string(trieTime))
				 << setw(15) << (hashTime == 0 ? "----" : to_string(hashTime)) << endl;

			trieTime = findAverage(trieYearBirthTimes);
			hashTime = findAverage(hashYearBirthTimes);
			trieSum += trieTime;
			hashSum += hashTime;
			cout << setw(45) << "Year Birth Search (avg.)"
				 << setw(15) << (trieTime == 0 ? "----" : to_string(trieTime))
				 << setw(15) << (hashTime == 0 ? "----" : to_string(hashTime)) << endl;

			trieTime = findAverage(trieYearRangeBirthTimes);
			hashTime = findAverage(hashYearRangeBirthTimes);
			trieSum += trieTime;
			hashSum += hashTime;
			cout << setw(45) << "Year Range Birth Search (avg.)"
				 << setw(15) << (trieTime == 0 ? "----" : to_string(trieTime))
				 << setw(15) << (hashTime == 0 ? "----" : to_string(hashTime)) << endl;

			trieTime = findAverage(trieYearByYearBirthTimes);
			hashTime = findAverage(hashYearByYearBirthTimes);
			trieSum += trieTime;
			hashSum += hashTime;
			cout << setw(45) << "Year-by-Year Birth Search (avg.)"
				 << setw(15) << (trieTime == 0 ? "----" : to_string(trieTime))
				 << setw(15) << (hashTime == 0 ? "----" : to_string(hashTime)) << endl;

			trieTime = findAverage(trieAllTimeBirthTimesPrefix);
			hashTime = findAverage(hashAllTimeBirthTimesPrefix);
			trieSum += trieTime;
			hashSum += hashTime;
			cout << setw(45) << "Prefix All-Time Birth Search (avg.)"
				 << setw(15) << (trieTime == 0 ? "----" : to_string(trieTime))
				 << setw(15) << (hashTime == 0 ? "----" : to_string(hashTime)) << endl;

			trieTime = findAverage(trieYearBirthTimesPrefix);
			hashTime = findAverage(hashYearBirthTimesPrefix);
			trieSum += trieTime;
			hashSum += hashTime;
			cout << setw(45) << "Prefix Year Birth Search (avg.)"
				 << setw(15) << (trieTime == 0 ? "----" : to_string(trieTime))
				 << setw(15) << (hashTime == 0 ? "----" : to_string(hashTime)) << endl;

			trieTime = findAverage(trieYearRangeBirthTimesPrefix);
			hashTime = findAverage(hashYearRangeBirthTimesPrefix);
			trieSum += trieTime;
			hashSum += hashTime;
			cout << setw(45) << "Prefix Year Range Birth Search (avg.)"
				 << setw(15) << (trieTime == 0 ? "----" : to_string(trieTime))
				 << setw(15) << (hashTime == 0 ? "----" : to_string(hashTime)) << endl;

			trieTime = findAverage(trieYearByYearBirthTimesPrefix);
			hashTime = findAverage(hashYearByYearBirthTimesPrefix);
			trieSum += trieTime;
			hashSum += hashTime;
			cout << setw(45) << "Prefix Year-by-Year Birth Search (avg.)"
				 << setw(15) << (trieTime == 0 ? "----" : to_string(trieTime))
				 << setw(15) << (hashTime == 0 ? "----" : to_string(hashTime)) << endl;

			trieTime = findAverage(trieTopNTimes);
			hashTime = findAverage(hashTopNTimes);
			trieSum += trieTime;
			hashSum += hashTime;
			cout << setw(45) << "TopN Search (avg.)"
				 << setw(15) << (trieTime == 0 ? "----" : to_string(trieTime))
				 << setw(15) << (hashTime == 0 ? "----" : to_string(hashTime)) << endl;

			cout << "---------------------------------------------------------------------------" << endl;

			cout << setw(45) << "Total Search Time (avg.)"
				 << setw(15) << (trieSum == 0 ? "----" : to_string(trieSum))
				 << setw(15) << (hashSum == 0 ? "----" : to_string(hashSum)) << endl;
			cout << endl;
		}
		else { //if (selection == 11) - Quitting
			cout << "Quitting..." << endl;
			running = false;
		}
		if (selection != 11)
			cout << "[Press 0 to Reprint the Menu]" << endl;
	}

	return 0;
}