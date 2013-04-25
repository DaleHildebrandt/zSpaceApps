#include "Parser.hpp"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

Parser::Parser(void)
{
}

Parser::~Parser(void)
{
}

bool Parser::stringIsInt(const string &str)
{
	bool valid = true;
	char* endptr;
	strtol(str.c_str(), &endptr, 10);

	if(*endptr)
		valid = false;

	return valid;
}

int Parser::string2Int(const string &str)
{
	char* endptr;
	int result = strtol(str.c_str(), &endptr, 10);

	if (*endptr)
	{
		throw 1;
		exit(1);
	}

	return result;
}

string Parser::int2String(int num)
{
	std::ostringstream result;
	result << num;
	return result.str();
}

bool Parser::stringIsDouble(const string &str)
{
	bool valid = true;
	char* endptr;
	strtod(str.c_str(), &endptr);

	if (*endptr)
		valid = false;

	return valid;
}

double Parser::string2Double(const string &str)
{
	char* endptr;
	double result = strtod(str.c_str(), &endptr);

	if (*endptr)
	{
		throw 1;
		exit(1);
	}

	return result;
}

bool Parser::stringIsDate(const string &str)
{
	bool valid = false;
	
	// str must be in the format ("dd/mm/yy h:mm");
	vector<string> spaceSplit = tokenize(str, " ");

	if (spaceSplit.size() == 2)
	{
		vector<string> slashSplit = tokenize(spaceSplit[0], "/");

		if ((slashSplit.size() == 3) &&
			(stringIsInt(slashSplit[0])) &&
			(stringIsInt(slashSplit[1])) &&
			(stringIsInt(slashSplit[2])))
		{
			vector<string> colonSplit = tokenize(spaceSplit[1], ":");

			if ((colonSplit.size() == 2) &&
				(stringIsInt(slashSplit[0])) &&
				(stringIsInt(slashSplit[1])))
			{
				valid = true;
			}

			else
				cout << "Parser::stringIsDate : invalid \":\" tokenization" << endl;
		}

		else
			cout << "Parser::stringIsDate : invalid \"/\" tokenization" << endl;
	}

	else
		cout << "Parser::stringIsDate : invalid \" \" tokenization" << endl;
	
	return valid;
}

double Parser::string2Date(const string &str)
{
	int minPerHour = 60;
	int minPerDay = 24*minPerHour;
	int minPerMonth = 30*minPerDay;
	int minPerYear = 12*minPerMonth;

	// str must be in the format ("dd/mm/yy h:mm");				
	// Converting str to minutes(int);
	// str must be in the format ("dd/mm/yy h:mm");
	vector<string> spaceSplit = tokenize(str, " ");
	vector<string> slashSplit = tokenize(spaceSplit[0], "/");
	vector<string> colonSplit = tokenize(spaceSplit[1], ":");

	double result = (string2Int(slashSplit[2]) * minPerYear) +
				 (string2Int(slashSplit[1]) * minPerMonth) +
				 (string2Int(slashSplit[0]) * minPerDay) +
				 (string2Int(colonSplit[0]) * minPerHour) +
				 string2Int(colonSplit[1]);

	return result;
}

string Parser::date2String(double date)
{
	string result, tmp;
	long remainder = (long)date;
	int t;
	int minPerHour = 60;
	int minPerDay = 24*minPerHour;
	int minPerMonth = 30*minPerDay;
	int minPerYear = 12*minPerMonth;
	char buffer[6];

	//separate out the components
	int y = (int)(remainder / minPerYear);
	remainder = remainder % minPerYear;

	int mo = (int)(remainder / minPerMonth);
	remainder = remainder % minPerMonth;

	int d = (int)(remainder / minPerDay);
	remainder = remainder % minPerDay;

	int h = (int)(remainder / minPerHour);
	remainder = remainder % minPerHour;

	int mi = remainder;


	//start building the string
	//dd
	tmp = int2String(d);
	if (tmp.size() == 1)
		tmp.insert(0, "0");

	result.append(tmp);
	result.append("/");

	//mm
	tmp = int2String(mo);
	if (tmp.size() == 1)
		tmp.insert(0, "0");

	result.append(tmp);
	result.append("/");

	//yyyy
	tmp = int2String(y);
	if (tmp.size() != 4)
		throw 1;

	result.append(tmp);
	result.append(" ");

	tmp = int2String(h);
	result.append(tmp);
	result.append(":");

	tmp = int2String(mi);
	if (tmp.size() == 1)
		tmp.insert(0, "0");

	result.append(tmp);

	//cout << "Parser::date2String : Result=" << result << endl;

	return result;
}

vector<string> Parser::tokenize(const string &str, const string &delimiters)
{
	//list of strings to be returned
	vector<string> result;

	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// Find first non-delimiter.
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos) {
		// Found a token, add it to the vector.
		result.push_back(str.substr(lastPos, pos - lastPos));

		// Skip delimiters.
		lastPos = str.find_first_not_of(delimiters, pos);

		// Find next non-delimiter.
		pos = str.find_first_of(delimiters, lastPos);
	}

	return result;
}