#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <algorithm>

using namespace std;

int main() {
	//regex (.+\w(?=\t))|(\d{4})|([^\[]+(?=\]))|([^\<]+(?=\>))|([^\{]+(?=\}))|((?<=\t)[^\t].+(?=[\s][(]\d{4}))
	//Expression("(.+\\w(?=\\t))|(\\d{4})|([^\\[]+(?=\\]))|([^\\<]+(?=\\>))|([^\\{]+(?=\\}))|([\\t].+(?=[\\s][(]\\d{4}))");
	ifstream file;
	ofstream outputFile;
	file.open("actors.list");
	outputFile.open("output.txt");

	string line;
	string output;
	
	string seperator = "; ";
	smatch match;

	if (file.is_open()) {
		string outputArray[11];
		//0 = date
		//1 = movieName
		//2 = actorName

		list<string> ArrayList;

		while (getline(file, line)) {
			regex dateExpression("(\\d{4})");
			while (regex_search(line, match, dateExpression)) {
				for (auto x : match) {
					outputArray[0] = x;
				}
			}

			regex movieExpression("(\\t\\w.+?(?=[)]))");
			while (regex_search(line, match, movieExpression)) {
				for (auto x : match) {
					outputArray[1] = x;
				}
			}

			regex actorNameExpression("");
			while (regex_search(line, match, actorNameExpression)) {
				for (auto x : match) {
					outputArray[2] = x;
				}
			}

			ArrayList.pop_back = outputArray;
		}
		outputFile << output;
	}

	file.close();
	return 0;
}