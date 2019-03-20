#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <thread>
#include <condition_variable>
#include <deque>
#include <algorithm>

using namespace std;


size_t stringCount(const std::string& referenceString,
	const std::string& subString) {

	const size_t step = subString.size();

	size_t count(0);
	size_t pos(0);

	while ((pos = referenceString.find(subString, pos)) != std::string::npos) {
		pos += step;
		++count;
	}

	return count;

}

int main() {
	ifstream LineCount;

	string inputFileName = "ratings.list";
	string outputFileName = "output.csv";

	ifstream file;
	file.open(inputFileName);
	LineCount.open(inputFileName);

	ofstream outputFile;
	outputFile.open(outputFileName);

	string line;
	string seperator = "; ";
	smatch match;

	int lineCount = 0;
	int percentage = -1;

	list<string> expressionList = { "([\\d|\\.]{10})","[\\s](\\d[0-9]{0,7})[\\s]","[\\s]([\\d+\\.+\\d]{3})[\\s]","\"(.*)\"","\\((\\d{4})\\)","\\{(.*)\\(","\\(#(\\d).","\\(#\\d.(\\d).","\\(#\\d.(\\d)." };

	if (LineCount.is_open()) { //total amount of lines
		string tmp;
		while (getline(LineCount, tmp)) {
			lineCount++;
		}
	}

	if (file.is_open()) {
		int count = 0;
		while (getline(file, line)) {
			count++;

			//UI
			if (int((double)count / (double)lineCount * 100) != percentage) {
				system("cls");

				cout << "File name:		" << inputFileName << endl;
				cout << "Output file:		" << outputFileName << endl;
				cout << endl;
				cout << "Amount of lines:	" << to_string(lineCount) << endl;
				cout << "Current line:		" << to_string(count) << endl;
				cout << endl;

				percentage = int((double)count / (double)lineCount * 100);

				string output = "[";
				for (int i = 0; i < 50; i++) {
					if (i < percentage/2)
						output += '=';
					else if (i == percentage/2)
						output += '>';
					else
						output += ' ';
				}
				output += ']';

				cout << percentage << "%" << endl;
				cout << output << endl;
			}

			string output = "";
			for (auto exp : expressionList) { //foreach expression in expression list => apply expression on line
				if (regex_search(line, match, regex(exp)))
					output += match.str(1) + seperator;

				else
					output += "NULL" + seperator;
			}

			if (stringCount(output, "NULL") != expressionList.size()) { //if output only contains null => skip
				outputFile << output << endl;
			}
		}
	}

	file.close();
	return 0;
}