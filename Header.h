#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <vector>
#include <string>
using namespace std;

class PropValue {
public:
	void addEntry(string p, string v) {
		propValuePair[p] = v;
	}

	void clear() {
		propValuePair.clear();
	}

	void showAllPropVal() {
		for (it = propValuePair.begin(); it != propValuePair.end(); ++it) {
			cout << "PROPERTY " << it->first << endl;
			cout << "VALUE " << it->second << endl;
		}
	}

private:
	map<string, string> propValuePair;
	map<string, string>::iterator it;
};



void readFromFileSaveToMap(const string& filename, map<string, PropValue>& mapName) {
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile)
		throw invalid_argument("Unable to open file " + filename);

	string mostRencentSectionName;

	PropValue PropValPair;

	for (string line; getline(inputFile, line); ) { // loop reading file line by line
		remove(line.begin(), line.end(), ' ');      // remove whitespaces

		string matchedSection, matchedProp, matchedVal;

		try {
			regex section(R"(\[(\w+)\])");
			regex propNvalue(R"((\w+)=(\w+))");

			smatch matchForTheFile;

			if (regex_search(line, matchForTheFile, section) && matchForTheFile.size() > 1) {
				matchedSection = matchForTheFile.str(1);
				cout << "SECTION " << matchedSection << endl;

				PropValPair.clear();
				mostRencentSectionName = matchedSection;
			}
			else if (regex_search(line, matchForTheFile, propNvalue) && matchForTheFile.size() > 1){
				matchedProp = matchForTheFile.str(1);
				matchedVal = matchForTheFile.str(2);
				cout << "PROPERTY " << matchedProp << endl;
				cout << "VALUE " << matchedVal << endl;

				PropValPair.addEntry(matchedProp, matchedVal);
				mapName[mostRencentSectionName] = PropValPair;
			}


		} catch (regex_error& e) {
			// Syntax error in the regular expression
		}

	}

	inputFile.close();
}
