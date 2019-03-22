// Parser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Wiebe de Boer
//Elon Gielink
//Casper Hooft
//Kevin haakma
//Nils Hettinga

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
	
	//string outputFilename;
	
	ifstream file;
	ofstream outputFile;

	string line;
	string seperator = "; ";
	smatch match;

	list<string> expressionList;

	enum outputFilename { actressesRoles, actresses, actorsRoles, actors, directed, directors, movies, countries, genres, soundtracks, ratings };

	//ratings
	switch (actressesRoles)
	{
	case actressesRoles:
		file.open("actresses.list"); //input actresses
		outputFile.open("roles.csv"); //output actresses
		expressionList = { "^.*?(?=\t)", "(\t(.*) \([0-9])\{1\}","\(([0-9]...)\)\{1\}","\[(.*)\]\{1\}" }; //actresses roles koppel
		//1= ^.*?(?=\t) //actress //748 steps
		//2= (\t(.*) \([0-9]){1}//movie //3066 steps
		//3= \(([0-9]...)\){1} //year //241 steps
		//4= \[(.*)\]{1} //role //121 steps
		break;
	case actresses:
		file.open("actresses.list"); //input actresses
		outputFile.open("actors.csv"); //output actresses
		expressionList = { "", "","","" }; //actresses
		//1=
		//2=
		//3=
		//4=
		break;
	case actorsRoles:
		file.open("actors.list"); //input actors
		outputFile.open("roles.csv"); //output actors
		expressionList = { "^.*?(?=\t)", "(\t(.*) \([0-9])\{1\}","\(([0-9]...)\)\{1\}","\[(.*)\]\{1\}" }; //actors roles koppel
		//1=
		//2=
		//3=
		//4=
		break;
	case actors:
		file.open("actors.list"); //input actors
		outputFile.open("actors.csv"); //output actors
		expressionList = { "", "","","" }; //actors
		//1=
		//2=
		//3=
		//4=
		break;
	case directed:
		file.open("directors.list"); //input directed
		outputFile.open("directed.csv"); //output directed
		expressionList = { "", "","","" }; //directed koppel
		//1=
		//2=
		//3=
		//4=
		break;
	case directors:
		file.open("directors.list"); //input directors
		outputFile.open("directors.csv"); //output directors
		expressionList = { "", "","","" }; //directors
		//1=
		//2=
		//3=
		//4=
		break;
	case movies:
		file.open("movies.list"); //input movies
		outputFile.open("movies.csv"); //output movies
		expressionList = { "","","" }; //movies
		//1=
		//2=
		//3=
		//4=
		break;
	case countries:
		file.open("countries.list"); //input countries
		outputFile.open("countries.csv"); //output countries
		expressionList = { "","","" }; //countries
		//1=
		//2=
		//3=
		//4=
		break;
	case genres:
		file.open("genres.list"); //input genres
		outputFile.open("genres.csv"); //output genres
		expressionList = { "","","" }; //genres
		//1=
		//2=
		//3=
		//4=
		break;
	case ratings:
		file.open("ratings.list"); //input ratings
		outputFile.open("ratings.csv"); //output ratings
		expressionList = { "([\\d|\\.]{10})","[\\s](\\d[0-9]{0,7})[\\s]","[\\s]([\\d+\\.+\\d]{3})[\\s]","\"(.*)\"","\\((\\d{4})\\)","\\{(.*)\\(","\\(#(\\d).","\\(#\\d.(\\d)." }; //ratings
		//1=
		//2=
		//3=
		//4=
		break;
	default:

		break;
	}
		

	//main parser
	if (file.is_open()) {

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




/*
using namespace std;
//using namespace regex;

int main() {
	//regex (.+\w(?=\t))|(\d{4})|([^\[]+(?=\]))|([^\<]+(?=\>))|([^\{]+(?=\}))|((?<=\t)[^\t].+(?=[\s][(]\d{4}))
	//Expression("(.+\\w(?=\\t))|(\\d{4})|([^\\[]+(?=\\]))|([^\\<]+(?=\\>))|([^\\{]+(?=\\}))|([\\t].+(?=[\\s][(]\\d{4}))");
	ifstream file;
	ofstream outputFile;
	file.open("actresses.list");
	outputFile.open("roles.txt");

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

			
			//regex dateExpression("(\\d{4})");
			//while (regex_search(line, match, dateExpression)) {
			//	for (auto x : match) {
			//		outputArray[0] = x;
			//	}
			//}
			

			
//string pattern = @"\p{ Sc }*(\s ? \d + [., ] ? \d*)\p{ Sc }*";
//	string replacement = "$1";
//string input = "$16.32 12.19 £16.29 €18.29  €18,29";
//string result = Regex.Replace(input, pattern, replacement);
//Console.WriteLine(result);


			//actress column 0
			outputArray[0] = "NULL";

			//date column 1
			regex dateExpression("\" \(([0-9]...)\)\{0\}");
			while (regex_search(line, match, dateExpression)) {
				for (auto x : match) {
					outputArray[1] = x;
				}
			}

			//movie column 2
			regex movieExpression("\"((.*)\")\{1\}");
			while (regex_search(line, match, movieExpression)) {
				for (auto x : match) {
					outputArray[2] = x;
				}
			}

			//role column 3
			regex roleExpression("\[(.*)\]\{0\}");
			while (regex_search(line, match, roleExpression)) {
				for (auto x : match) {
					outputArray[3] = x;
				}
			}

			
			//regex actorNameExpression("");
			//while (regex_search(line, match, actorNameExpression)) {
			//	for (auto x : match) {
			//		outputArray[2] = x;
			//	}
			//}
			

			ArrayList.pop_back = outputArray;
		}
		outputFile << output;
	}

	file.close();
	return 0;
}
*/

/*
int main() {
	ifstream file;
	ofstream outputFile;
	file.open("actors.list");
	outputFile.open("output.txt");

	string line;
	string output;

	string seperator = "; ";
	smatch match;

	if (file.is_open()) {
		string outputarray[11];
		list<string> Arraylist;
		while (getline(file, line)) {
			regex expression;
			while (regex_search(line, match, expression)) {
				for (auto x : match) {
					output += x;
				}
				output += "\n";
			}
			outputFile << output;
		}

	}

	file.close();
	return 0;
}
*/


/*
int main() {
	//regex (.+\w(?=\t))|(\d{4})|([^\[]+(?=\]))|([^\<]+(?=\>))|([^\{]+(?=\}))|((?<=\t)[^\t].+(?=[\s][(]\d{4}))

	regex (.+\w(?=\t))|(\d{4})|([^\[]+(?=\]))|([^\<]+(?=\>))|([^\{]+(?=\}))|((?<=\t)[^\t].+(?=[\s][(]\d{4}))
	ifstream file;
	ofstream outputFile;
	file.open("special-effects-companies.list");
	outputFile.open("output.txt");

	string line;
	string output;

	string seperator = "; ";
	char charArray[] = { '\"','\"', '(', ')','{','}','[',']','(',')' };

	if (file.is_open()) {
		while (getline(file, line)) {
			int valCount = 0;
			int charPos = 0;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == charArray[charPos]) {
					valCount++;
					i++;
					while (line[i] != charArray[charPos + 1] && i < line.size()) {
						output += line[i];
						i++;
					}
					output += seperator;
					charPos = charPos + 2;
				}
				else if (line[i] == charArray[charPos + 2]) {
					output += "NULL" + seperator;
					valCount++;
					charPos = charPos + 2;
				}
			}
			output += "\n";
		}
		outputFile << output;

	}

	file.close();
	return 0;
}
*/


/*
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	ifstream file;
	ofstream outputFile;
	file.open("special-effects-companies.list");
	outputFile.open("test.txt");

	string line;
	string output;
	string str3;
	size_t pos;
	size_t pos2;

	if (file.is_open()) {
		while (getline(file, line)) {


			pos = line.find("(19");  // position of year in line
			if (pos < 1) {
				pos2 = line.find("(20"); //position of year in line
				str3 = line.substr(pos2,4); //get from line till end
				output += str3 + "\n";
			}
			else if (pos >=1) {
				str3 = line.substr(pos,4); //get from line till end
				output += str3 + "\n";
			}		
			

			
			for (std::size_t pos : line.find("(19")) {
				int count = 0;
				if (subc == "(20") {
					while (line[count + 1] != '(20') {
						output += line[count + 1];
						count++;
					}
					output += ", \n";
				}
				if (subc == "(19") {
					while (line[count + 1] != ')') {
						output += line[count + 1];
						count++;
					}
					output += ", \n";
				}
			}
			
		}
		outputFile << output;

	}

	file.close();
	return 0;
}
*/

/*

int main() {
	ifstream file;
	ofstream outputFile;
	file.open("special-effects-companies.list");
	outputFile.open("test.txt");

	string line;
	string output;

	if (file.is_open()) {
		while (getline(file, line)) {
			int valCount = 0;
			for (int i = 0; i < line.size(); i++) {

				if (line[i] == '\"' && valCount == 0) {
					valCount++;
					i++;
					while (line[i] != '\"' && i < line.size()) {
						output += line[i];
						i++;
					}
					output += ", ";
				}

				if (line[i] == '(' && valCount == 1) {
					valCount++;
					i++;
					while (line[i] != ')' && i < line.size()) {
						output += line[i];
						i++;
					}
					output += ", ";
				}
				else if (line[i] == '(' && valCount == 0) {
					output += "NULL,";
					valCount++;
				}

				if (line[i] == '{' && valCount == 2) {
					valCount++;
					i++;
					while (line[i] != '}' && i < line.size()) {
						output += line[i ];
						i++;
					}
					output += ", ";
				}
				else if (line[i] == '{' && valCount == 1) {
					output += "NULL,";
					valCount++;
				}

				/*
				if (line[i] == ' ' && valCount == 3) {
					valCount++;
					i++;
					while (line[i] != '[' && i < line.size()) {
						output += line[i];
						i++;
					}
					output += ", ";
				}
				else if (line[i] == ' ' && valCount == 2) {
					output += "NULL,";
					valCount++;
				}

if (line[i] == '[' && valCount == 3) {
	valCount++;
	i++;
	while (line[i] != ']' && i < line.size()) {
		output += line[i];
		i++;
	}
	output += ", ";
}
else if (line[i] == '[' && valCount == 2) {
	output += "NULL,";
	valCount++;
}

if (line[i] == '(' && valCount == 4) {
	valCount++;
	i++;
	while (line[i] != ')' && i < line.size()) {
		output += line[i];
		i++;
	}
	output += ", ";
}
else if (line[i] == '(' && valCount == 3) {
	output += "NULL,";
	valCount++;
}
			}
			output += "\n";
		}
		outputFile << output;

	}

	file.close();
	return 0;
}

*/



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
