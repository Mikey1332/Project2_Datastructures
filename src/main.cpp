#include <iostream>
#include "trie.h"
#include "hash.h"
using namespace std;

int main(){
	Trie trie;
	// HashTable hash;
	string line, name, selectionString;
	char sex = ' ';
	bool running = true;
	int selection = -1;
	int year = -1;
	int year2 = -1;
	int N = -1;
	// vector<string> arguments;

	//Do File Parsing:
	//trie.insert(...);
	//hash.insert(...);

	//User Selection
	cout << "=== Baby Name Search ===\n"
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
		"11. Quit\n" << endl;

	while (running) {
		selection = -1;
		while (selection == -1) {
			line.clear();
			cout << "Please enter your selection (#1-11): ";
			getline(cin, line);
			try {
				selection = stoi(line);
			}
			catch (exception& e) {
				cout << "Please enter a valid number." << endl;
			}
			if (selection < 1 || selection > 11) {
				cout << "Please enter a number between 1 and 11." << endl;
				selection = -1;
			}
		}

		//Name/Prefix Insert:
		if (selection != 10 && selection != 11) {
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
				cout << ": " << endl;
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
		if (selection != 10 && selection != 11) {
			//Sex Selection
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

		if (selection == 1) {
			cout << "You chose total births of \"" << name << "\" (" << sex << ") for all time." << endl;

			cout << "Trie: " << endl;
			cout << "There are [" <<
			trie.getAllTimeTotal(name, sex, false) <<
			"] births for \"" << name << "\" (" << sex << ") for all time." << endl;
			cout << "------------------------------------" << endl;
			cout << "Hash: " << endl;
			// cout << "There are [" <<
			// hash.getAllTimeTotal(name, sex, false) <<
			// "] births for \"" << name << "\" (" << sex << ") for all time." << endl;
		}
		else if (selection == 2) {
			cout << "You chose total births of \"" << name << "\" (" << sex << ") in " << year << "." << endl;

			cout << "Trie: " << endl;
			cout << "There are [" <<
			trie.getYearTotal(name, sex, year, false) <<
			"] births for \"" << name << "\" (" << sex << ") in " << year << "." << endl;
			cout << "------------------------------------" << endl;
			cout << "Hash: " << endl;
			// cout << "There are [" <<
			// hash.getYearTotal(name, sex, year, false) <<
			// "] births for \"" << name << "\" (" << sex << ") in " << year << "." << endl;
		}
		else if (selection == 3) {
			cout << "You chose total births of \"" << name << "\" (" << sex << ") from " << year << " to " << year2 << "." << endl;

			int trieTotal = 0;
			int hashTotal = 0;
			for (int y = year; y <= year2; y++) {
				trieTotal += trie.getYearTotal(name, sex, y, false);
				// hashTotal += hash.getYearTotal(name, sex, y, false);
			}
			cout << "Trie: " << endl;
			cout << "There are [" << trieTotal << "] births for \"" << name << "\"  (" << sex << ") from " << year << " to " << year2 << "." << endl;
			cout << "------------------------------------" << endl;
			cout << "Hash: " << endl;
			// cout << "There are [" << hashTotal << "] births for \"" << name << "\"  (" << sex << ") from " << year << " to " << year2 << "." << endl;
		}
		else if (selection == 4) {
			cout << "You chose the year-by-year trend of \"" << name << "\" (" << sex << ")." << endl;
		}
		else if (selection == 5) {
			cout << "You chose total births of prefix \"" << name << "-\" (" << sex << ") for all time." << endl;

			cout << "Trie: " << endl;
			cout << "There are [" <<
			trie.getAllTimeTotal(name, sex, true) <<
			"] births of prefix \"" << name << "-\" (" << sex << ") for all time." << endl;
			cout << "------------------------------------" << endl;
			cout << "Hash: " << endl;
			// cout << "There are [" <<
			// hash.getAllTimeTotal(name, sex, true) <<
			// "] births of prefix \"" << name << "-\" (" << sex << ") for all time." << endl;
		}
		else if (selection == 6) {
			cout << "You chose total births of prefix \"" << name << "-\" (" << sex << ") in " << year << "." << endl;

			cout << "Trie: " << endl;
			cout << "There are [" <<
			trie.getYearTotal(name, sex, year, true) <<
			"] births of prefix \"" << name << "-\" (" << sex << ") in " << year << "." << endl;
			cout << "------------------------------------" << endl;
			cout << "Hash: " << endl;
			// cout << "There are [" <<
			// hash.getYearTotal(name, sex, year, true) <<
			// "] births of prefix \"" << name << "-\" (" << sex << ") in " << year << "." << endl;
		}
		else if (selection == 7) {
			cout << "You chose total births of prefix \"" << name << "-\" (" << sex << ") from " << year << " to " << year2 << "." << endl;

			int trieTotal = 0;
			int hashTotal = 0;
			for (int y = year; y <= year2; y++) {
				trieTotal += trie.getYearTotal(name, sex, y, true);
				// hashTotal += hash.getYearTotal(name, sex, y, true);
			}
			cout << "Trie: " << endl;
			cout << "There are [" << trieTotal << "] births of prefix \"" << name << "-\"  (" << sex << ") from " << year << " to " << year2 << "." << endl;
			cout << "------------------------------------" << endl;
			cout << "Hash: " << endl;
			// cout << "There are [" << hashTotal << "] births of prefix \"" << name << "-\"  (" << sex << ") from " << year << " to " << year2 << "." << endl;
		}
		else if (selection == 8) {
			cout << "You chose the year-by-year trend of prefix \"" << name << "-\" (" << sex << ")." << endl;
		}
		else if (selection == 9) {
			cout << "You chose the top " << N << " names for prefix \"" << name << "-\" (" << sex << ")";
			if (year != -1)
				cout << " in " << year;
			cout << "." << endl;
		}
		else if (selection == 10) {
			cout << "You chose to run a performance benchmark." << endl;
		}
		else { //if (selection == 11) - Quitting
			cout << "Quitting..." << endl;
			running = false;
		}
		cout << endl;
	}

	return 0;
}