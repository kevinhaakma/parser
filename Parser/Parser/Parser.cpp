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
	//regex (.+\w(?=\t))|(\d{4})|([^\[]+(?=\]))|([^\<]+(?=\>))|([^\{]+(?=\}))|((?<=\t)[^\t].+(?=[\s][(]\d{4}))
	//Expression("(.+\\w(?=\\t))|(\\d{4})|([^\\[]+(?=\\]))|([^\\<]+(?=\\>))|([^\\{]+(?=\\}))|([\\t].+(?=[\\s][(]\\d{4}))");
	ifstream file;
	ofstream outputFile;
	file.open("ratings.list");
	outputFile.open("output.csv");

	string line;
	string seperator = "; ";
	smatch match;
	list<string> expressionList = { "([\\d|\\.]{10})","[\\s](\\d[0-9]{0,7})[\\s]","[\\s]([\\d+\\.+\\d]{3})[\\s]","\"(.*)\"","\\((.*)\\)","\\{(.*)\\(","\\(#(\\d).","\\(#\\d.(\\d)." };

	if (file.is_open()) {
		//0 = date
		//1 = movieName
		//2 = actorName
		//3 = roleName

		int count = 0;
		while (getline(file, line)) {
			count++;

			if (count % 1000 == 0) {
				cout << count << endl;
				//file.close();
				//return 0;
			}

			string output = "";
			for (auto exp : expressionList) {
				if (regex_search(line, match, regex(exp)))
					output += match.str(0) + seperator;

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