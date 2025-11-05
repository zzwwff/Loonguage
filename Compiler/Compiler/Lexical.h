#pragma once
#include <cstring>
#include "Tokens.h"
#include "LoonParser.hpp"
#include "LoonScanner.h"
#include "SymbolTable.h"
#include "NodeProgram.h"
#include "Error.h"

namespace Loonguage {

	class Lexical
	{
		Loonguage::SymbolTable<std::string> strTable, idenTable;
		NodeProgram* program;
		LoonScanner::Scanner scanner;
		LoonScanner::Parser parser;
		Errors errs;
	public:
		Tokens tokens;
		//cin of file path
		Lexical();
		void parse();
		void dump() const;
	};
}


