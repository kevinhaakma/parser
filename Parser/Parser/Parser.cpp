﻿// Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Wiebe de Boer
//Elon Gielink
//Casper Hooft
//Kevin haakma
//Nils Hettinga
//Groep 10


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
#include <sstream>
#include <vector>

using namespace std;

string uiOutput(string inputFileName, string outputFileName, int totalLineCount, int lineCount, int percentage);
size_t stringCount(const std::string& referenceString, const std::string& subString);
std::vector<std::string> split(std::string strToSplit, char delimeter);

int main() {
	string inputFileName; //input file name
	string outputFileName; //output file name

	string line; //line for record
	smatch match; //match
	string seperator = "|"; //string seperator for csv column

	list<string> expressionList; //list expressions

	//enum with output choices
	enum outputFilename { actressesRoles, actresses, actorsRoles, actors, directed, directors, movies, countries, genres, soundtracks, ratings };
	list <string> fileNames = { "0: actressesRoles", "1: actresses", "2: actorsRoles", "3: actors", "4: directed", "5: directors", "6: movies", "7: countries", "8: genres", "10: ratings" };
	//0 actressesRoles (actor index) (needs to be added to roles) //Casper, Elon, 
	//1 actresses (needs to be added to actors) (gender needs to be added) //Wiebe, Elon, Casper, Kevin
	//2 actorsRoles (actor index) //Wiebe, Kevin, Elon, Casper
	//3 actors * (gender needs to be added) //Kevin, Elon
	//4 directed * (director index) //Casper, Elon
	//5 directors * //Casper, Wiebe, Elon
	//6 movies * (movie index) //Casper, Elon, Wiebe
	//7 countries * //Casper, Elon, Wiebe
	//8 genres * //Elon, Wiebe
	//9 soundtracks //Elon
	//10 ratings * //Elon, Kevin, Wiebe

	int input;
	for (string x : fileNames)
	{
		cout << x << endl;
	}


	cout << "Please enter number: " << endl;
	cin >> input;

	//ratings
	switch (input)
	{
	case actressesRoles:
		inputFileName = "actresses.list"; //input actresses
		outputFileName = "actressesRoles.csv"; //output actresses
		//expressionList = { "(.*\\w|.*\\w\\))\\t", "\\t(\\w.*|\\\"\\w.*)(\\([0-9]|\\(\\?{4}\\))","\\(([0-9]...)\\){1}","\\[(.*)\\]{1}" };\[(.*){1}\]
		//expressionList = { "(.*\\w|.*\\w\\))\\t", "\\t((\\\"|\\w).*)\\s\\([0-9]{4}", "\\(([0-9]...)\\){1}", "\\{(.*)\\(","\\(#(\\d{1,10}).",".(\\d{1,10})\\)\\\}","\\[(.*){1}\\]" };
		//THIS ONE HAS NO 7TH COLUMexpressionList = { "(.*\\w'|.*\\w|.*\\w\\))\\t", "\\t((\\\"|\\w).*)\\s\\([0-9]{4}", "\\((\\w{4})(\\) | \\ \/ )", "\\{(.*)\\(","\\(#(\\d{1,10}).",".(\\d{1,10})\\)\\\}" };
		expressionList = { "(.*\\w|.*\\w\\))\\t", "\\t((\\\"|\\w).*)\\s\\([0-9]{4}", "\\((\\d{4})\\)", "\\\{(.*)\\(#","\\(#(\\d{1,10}).",".(\\d{1,10})\\)\\\}", "\\[(.*)\\]" };
		//backup first: ^[^\t](\w.*?|.*?)\t als de roles niet correct worden geprint, probeer deze s
		//1= (.*\w|.*\w\))\t //actress //748 steps
		//(.*\w'|.*\w|.*\w\))\t
		//2= \t(\w.*|\"\w.*)(\([0-9]|\(\?{4}\))//movie //3066 steps
		//3= ([0−9]...)([0-9]...)([0−9]...){1} //year //241 steps
		//4= \[(.*)\]{1} //role //121 steps
		//4 nieuw = (.*)\]{1}
		break;
	case actresses:
		inputFileName = "actresses.list"; //input actresses
		outputFileName = "actressesActors.csv"; //output actresses
		expressionList = { "^(\\w.*?)\\t" }; //actresses
		//1= actor ^(\w.*?)\t
		//to do gender en tabs als null eruit
		break;
	case actorsRoles:
		inputFileName = "actors.list"; //input actors
		outputFileName = "actorsRoles.csv"; //output actors
		//expressionList = { "^.*?(?=\\t)", "(\\t(.*) \\([0-9])\{1\}","\\(([0-9]...)\\)\{1\}","\\[(.*)\\]\{1\}" }; //actors roles koppel
		//expressionList = { "^.*?(?=\\t)", "(\\t(.*) \\([0-9])\{1\}","\\(([0-9]...)\\)\{1\}","\\[(.*)\\]\{1\}" }; //actors roles koppel
		//expressionList = { "(.*\\w|.*\\w\\))\\t", "\\t((\\\"|\\w).*)\\s\\([0-9]{4}", "\\(([0-9]...)\\){1}", "\\{(.*)\\(","\\(#(\\d{1,10}).",".(\\d{1,10})\\)\\\}","\\t(\\d{4}|\\d{4}\\-.*)$" };
		expressionList = { "(.*\\w|.*\\w\\))\\t", "\\t((\\\"|\\w).*)\\s\\([0-9]{4}", "\\((\\d{4})\\)", "\\\{(.*)\\(#","\\(#(\\d{1,10}).",".(\\d{1,10})\\)\\\}", "\\[(.*)\\]" };
		//expressionList = { "(.*\\w|.*\\w\\))\\t", "\\t(.*)\{1\}\\s\\([0-9]", "\\((\\d{4})\\)", "\\{(.*)\\(","\\(#(\\d{1,10}).",".(\\d{1,10})\\)\\\}","\\t(\\d{4}|\\d{4}\\-.*)$" }; //actors roles koppel
		//1 actor = "(.*\\w|.*\\w\\))\\t"
		//2 movie = "\\t((\\\"|\\w).*)\\s\\([0-9]{4}"
		//3 year = "\\((\\d{4})\\)"
		//new year = "\((\w{4})(\)|\/)"
		//4 serie = "\\{(.*)\\(","\\(#(\\d{1,10})."
		//5 season = ".(\\d{1,10})\\)\\\}"
		//6 episode = "\\t(\\d{4}|\\d{4}\\-.*)$"
		//7 role = "\\[(.*)\\]{1}"
		break;
	case actors:
		inputFileName = "actors.list"; //input actors
		outputFileName = "actorsActors.csv"; //output actors
		expressionList = { "^(\\w.*?)\\t" }; //actors
		//1= actor ^.*?(?=\t)
		//to do gender en tabs als null eruit
		break;
	case directed:
		inputFileName = "directors.list"; //input directed
		outputFileName = "directed.csv"; //output directed
		expressionList = { "(.*\\w|.*\\w\\))\\t", "\\t(\\w.*) (\\([0-9]|\\(\\?{4}\\))", "\\s{2,}\\(([a-zA-Z](.*?)director(.*?)|director)\\)" };
		break;
	case directors:
		inputFileName = "directors.list"; //input directors
		outputFileName = "directors.csv"; //output directors
		expressionList = { "^(\\w.*?)\\t" }; //directors
		//1= director ^.*?(?=\t)
		//tabs als null eruit
		break;
	case movies:
		inputFileName = "movies.list"; //input movies
		outputFileName = "movies.csv"; //output movies
		expressionList = { "^\\\"(.*?)\\\"","\\((\\d{4})\\)","\\{(.*)\\(","\\(#(\\d{1,10}).",".(\\d{1,10})\\)\\\}","\\t(\\d{4}|\\d{4}\\-.*)$" }; //movies
		//1= movieName ^\"(.*?)\"
		//2= year \((\d{4})\)
		//3= serieName \{(.*)\(
		//4= serieSeason \(#(\d{1,10}).
		//5= episode number .(\d{1,10})\)}
		//6= end season \t(\d{4}|\d{4}\-.*)$
		break;
	case countries:
		inputFileName = "countries.list"; //input countries
		outputFileName = "countries.csv"; //output countries
		expressionList = { "^\"(.*?)\"", "\\((\\d{4})\\)", "\\{(.*)\\(#", "\\(#(\\d).", "\\(#\\d.(\\d).", "\\s(\\w+-+\\w+|\\w+)$" }; //countries
		//1= movie title = ^"(.*?)"
		//2=	jaar = \((\d{ 4 })\)
		//3=	episodenaam = { (.*)\(#
		//4=	season = \(#(\d).
		//5=	episode = \(#\d.(\d).
		//6=	country = \s(\w + -+\w + | \w + )$
		break;
	case genres:
		inputFileName = "genres.list"; //input genres
		outputFileName = "genres.csv"; //output genres
		expressionList = { "^(.*?)\\((\\d)","\\((\\d{4})\\)","\\{(.*?)(\\(|\\\})","\\(#(\\d{1,2}).","\\(#\\d{1,2}.(\\d{1,2})\\)\\\}","\\s(\\w+-+\\w+|\\w+)$" }; //genres
		//1= Title = ^ (.*)\(
		//2= jaar = \((\d{ 4 })\)
		//3= episodenaam = { (.*)\(#
		//4= season = \(#(\d).
		//5= episode = \(#\d.(\d).
		//6= genre = \s(\w + -+\w + | \w + )$
		break;
	case soundtracks:
		inputFileName = "soundtracks.list"; //input sounndtracks
		outputFileName = "soundtracks.csv"; //output soundtracks
		expressionList = { "(\\# (.*) \\([0-9])\{1\}","(\\(([0-9]...)\\))\{1\}", "\\-\\s(.*)\\s\\s\{1\}", "\\s\\s(By|by|Written by|Music by|Composed by) (.*)\{1\}", "Performed by (.*)\{1\}" }; //soundtracks
		//1= movie (\# (.*) (\\# (.*) \\([0-9])\{1\}
		//2= year (\\(([0-9]...)\\))\{1\}
		//3= soundtrack \\-\\s(.*)\\s\\s\{1\}
		//4= composed/written \s\s(By|by|Written by|Music by|Composed by) (.*)\{1\}
		//5= performer Performed by (.*){1}
		//multi?
		break;
	case ratings:
		inputFileName = "ratings.list"; //input ratings
		outputFileName = "ratings.csv"; //output ratings
		expressionList = { "([\\d|\\.]{10})","[\\s](\\d[0-9]{0,7})[\\s]","\\d\\s{3}(\\d+\\.\\d)","\\d\\.\\d\\s{2}(\\\".*?|\\w.*?)\\(","\\((\\d{4})\\)","\\{(.*)\\(","\\(#(\\d)\\.","\\(#\\d.(\\d{1,10})" }; //ratings
		//1=distribution ([\d|\.]{10})
		//2=votes [\s](\d[0-9]{0,7})[\s]
		//3=ratings \d\s{3}(\d+\.\d)
		//4=title \d\.\d\s{2}(\".*?|\w.*?)\(
		//5=year \((\d{4})\)
		//6=serie title \{(.*)\(
		//7=season \(#(\d)\.
		//8=episode \(#\d.(\d{1,10})
		break;
	default:
		//default do nothing here
		inputFileName = "input.list"; //input list file
		outputFileName = "output.csv"; //output csv file
		expressionList = { "","","" }; //expression list
		break;
	}

	system("cls");
	ifstream file(inputFileName); //input file
	ifstream totalLineCountFile(inputFileName); //line count
	ofstream outputFile(outputFileName); //output file

	//main
	int lineCount = 0;
	if (outputFileName == "actressesActors.csv") {
		lineCount = 20152659;
	}
	else {
		lineCount = 0;
	}

	int totalLineCount = 0;
	int lastPercentage = 0;
	for (totalLineCount = 0; std::getline(totalLineCountFile, line); ++totalLineCount); //counts total amount of lines

	if (file.is_open()) {
		string lastActor = "";
		while (getline(file, line)) { //get nextline from file and store it in line
			lineCount++;

			//UI
			int percentage = int((double)lineCount / (double)totalLineCount * 100);
			if (percentage != lastPercentage) {
				lastPercentage = percentage;
				system("cls");
				cout << uiOutput(inputFileName, outputFileName, totalLineCount, lineCount, percentage);
			}

			//OUTPUT STRING
			string output = "";
			//ADD ID NUMBER FOR PRIMARY KEY
			//output = to_string(lineCount) + seperator;

			//REGEX
			for (auto exp : expressionList) { //foreach expression in expression list => apply expression on line
				if (regex_search(line, match, regex(exp)) && match.str(1) != "")
					output += match.str(1) + seperator;

				else
					output += "0" + seperator;
			}

			if (outputFileName == "actorsActors.csv") {
				output += "0";
			}
			else if (outputFileName == "actressesActors.csv") {
				output += "1";
			}
			if (outputFileName == "actressesRoles.csv" | outputFileName == "actressesActors.csv" | outputFileName == "actorsRoles.csv" | outputFileName == "actorsActors.csv" | outputFileName == "directors.csv" | outputFileName == "directed.csv") {
				vector<string> v = split(output, seperator[0]);

				if (v[0].find("0") != std::string::npos && lastActor != "") {
					v[0] = lastActor;

					output = "";
					for (auto s : v) {
						output += s + seperator;
					}
				}
				else if (v[0].find("0") == std::string::npos) {
					lastActor = v[0];
				}
			}

			//STRING COUNT
			if (stringCount(output, "0") != expressionList.size()) { //if output only contains null => skip
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

//Splits code on delimiter
std::vector<std::string> split(std::string strToSplit, char delimeter)
{
	std::stringstream ss(strToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (std::getline(ss, item, delimeter))
	{
		item.erase(std::remove_if(item.begin(), item.end(), ::isspace), item.end());
		splittedStrings.push_back(item);
	}
	return splittedStrings;
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
