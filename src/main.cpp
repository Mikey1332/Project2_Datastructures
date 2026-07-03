#include <iostream>
#include "trie.h"
#include "hash.h"
using namespace std;

int main(){
	Trie trie;
	// HashTable hash;
	string line, name, selectionString;
	bool running = true;
	int selection = -1;
	vector<string> arguments;

	//Do File Parsing:
	//trie.insert(...);
	//hash.insert(...);

	//User Selection
	cout << "=== Baby Name Search ===\n"
		"1. Name - total births (all-time)\n"
		"2. Name - births in a specific year\n"
		"3. Name - births across a year range\n"
		"4. Name - year-by-year trend\n"
		"5. Prefix - matches in a specific year\n"
		"6. Prefix - total births (all-time, combined)\n"
		"7. Prefix - matches across a year range\n"
		"8. Prefix - year-by-year trend (combined)\n"
		"9. Prefix - top N names (sex/year filter)\n"
		"10. Run performance benchmark\n"
		"11. Quit\n\n"
		"Example Response: 1 \"Michael\"" << endl;

	while (running) {
		line = "";
		getline(cin, line);
		line += " ";

		// while (!line.empty()) {
		// 	arguments.push_back(line.substr(0, line.find(" ")));
		// 	line = line.substr(line.find(" ")+1);
		// }

		selectionString = line.substr(0, line.find(" "));
		line = line.substr(line.find(" ")+1);

		//For name
		if (line[0]=='"') {
			line = line.substr(1, line.size());
			name = line.substr(0, line.find('"'));
			line = line.substr(line.find('"')+2);
		}

		try {
			selection = stoi(selectionString);
		}
		catch (exception& e) {
			cout << "Please enter a valid number" << endl;
		}

		//Selections:

		if (selection < 1 || selection > 11) {
			cout << "Please enter a number between 1 and 11" << endl;
		}
		else if (selection == 1) {
			cout << "Trie: " << endl;
			cout << trie.getTotal(name, 'M', false) + trie.getTotal(name, 'F', false) << endl;

			// cout << "Hash: " << endl;
			// cout << hash.getTotal(name, 'M', false) + hash.getTotal(name, 'F', false) << endl;
		}
		else if (selection == 5) {
			cout << "Trie: " << endl;
			cout << trie.getTotal(name, 'M', true) + trie.getTotal(name, 'F', true) << endl;

			// cout << "Hash: " << endl;
			// cout << hash.getTotal(" ", 'M', true) + hash.getTotal(" ", 'F', true) << endl;
		}
		else if (selection == 11)
			running = false;
	}

	return 0;
}
// test 2 - kaiden