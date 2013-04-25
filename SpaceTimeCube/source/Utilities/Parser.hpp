#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include <vector>
#include <string>

class Parser
{
	public:
		Parser(void);
		~Parser(void);

		bool stringIsInt(const std::string &str);
		int string2Int(const std::string &str);
		static std::string int2String(int num);

		bool stringIsDouble(const std::string &str);
		double string2Double(const std::string &str);

		bool stringIsDate(const std::string &str);
		double string2Date(const std::string &str);
		static std::string date2String(double date);

		std::vector<std::string> tokenize(const std::string &str,
										  const std::string &delimiter);

};

#endif