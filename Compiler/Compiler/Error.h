#pragma once
#include <string>
#include <iostream>
#include <vector>
namespace Loonguage {
	class Error
	{
	public:
		std::string status;
		int line;
		std::string msg;
		Error(std::string, int, std::string);
		Error(std::string, std::string);
		void dump(std::ostream&) const;
	};

	class Errors:
		public std::vector<Error>
	{
	public:
		void dump(std::ostream&) const;
	};
}
