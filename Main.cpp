#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
#include <vector>
#include <string>

#include "Header.h"
using namespace std;


int main() {

	map<string, PropValue> sectionPropValue;
	readFromFileSaveToMap("INI_File.ini", sectionPropValue);

	cout << "\n############### Contents in map###############\n" << endl;

	map<string, PropValue>::iterator itSecPV;
	//map<string, string>::iterator innerit;

	for (itSecPV = sectionPropValue.begin(); itSecPV != sectionPropValue.end(); ++itSecPV) {
		cout << "SECTION " << itSecPV->first << endl;
		(itSecPV->second).showAllPropVal();
	}

	system("pause");
	return 0;
}
