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

string uiOutput(string inputFileName, string outputFileName, int totalLineCount, int lineCount, int percentage);
size_t stringCount(const std::string& referenceString, const std::string& subString);

int main() {
	string inputFileName = "ratings.list";
	string outputFileName = "output.csv";

	ifstream file(inputFileName);
	ifstream totalLineCountFile(inputFileName);
	ofstream outputFile(outputFileName);

	string line;
	smatch match;
	string seperator = "; ";

	list<string> expressionList = { "([\\d|\\.]{10})","[\\s](\\d[0-9]{0,7})[\\s]","[\\s]([\\d+\\.+\\d]{3})[\\s]","\"(.*)\"","\\((\\d{4})\\)","\\{(.*)\\(","\\(#(\\d).","\\(#\\d.(\\d)." };

	int lineCount = 0;
	int totalLineCount = 0;
	int lastPercentage = 0;
	for (totalLineCount = 0; std::getline(totalLineCountFile, line); ++totalLineCount); //counts total amount of lines

	if (file.is_open()) {
		while (getline(file, line)) { //get nextline from file and store it in line
			lineCount++;

			//UI
			int percentage = int((double)lineCount / (double)totalLineCount * 100);
			if (percentage != lastPercentage) {
				lastPercentage = percentage;
				system("cls");
				cout << uiOutput(inputFileName, outputFileName, totalLineCount, lineCount, percentage);
			}

			//REGEX
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

//Method to count the amount of times a word occurs in a substring
size_t stringCount(const std::string& referenceString, const std::string& subString) {
	const size_t step = subString.size();

	size_t count(0);
	size_t pos(0);

	while ((pos = referenceString.find(subString, pos)) != std::string::npos) {
		pos += step;
		++count;
	}
	return count;
}

//generates the output for the UI.
//Displays the current file, outputfile, total amount of lines, Current line, percentage
string uiOutput(string inputFileName, string outputFileName, int totalLineCount, int lineCount, int percentage) {
	string output = "File name:		" + inputFileName + "\nOutput file:		" + outputFileName + "\n\nAmount of lines:	" + to_string(totalLineCount) + "\nCurrent line:		" + to_string(lineCount) + "\n\n";
	output += to_string(percentage) + "%\n";
	output += "[";
	for (int i = 0; i < 50; i++) {
		if (i < percentage / 2) output += '=';
		else if (i == percentage / 2) output += '>';
		else output += ' ';
	}
	output += ']';
	return output;
}