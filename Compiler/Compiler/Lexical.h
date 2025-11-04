#pragma once
#include <cstring>
#include "Tokens.h"
#include "LoonParser.hpp"
#include "LoonScanner.h"

namespace Loonguage {

	class Lexical
	{
		Loonguage::SymbolTable<std::string> strTable, idenTable;

		LoonScanner::Scanner scanner;
		LoonScanner::Parser parser;
	public:
		Tokens tokens;
		//cin of file path
		Lexical();
		void parse();
		void dump() const;
	};
}


