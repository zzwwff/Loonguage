#pragma once
#include <cstring>
#include <map>
#include "Tokens.h"
#include "LoonParser.hpp"
#include "LoonScanner.h"
#include "SymbolTable.h"
#include "NodeProgram.h"
#include "Error.h"
#include "FunctionDeco.h"

namespace Loonguage {

	class Compiler
	{
		using Symbol = SymbolTable<std::string>::Symbol;
		//Phase 1 ~ 2
		//for lexical and syntax analysis
		LoonScanner::Scanner scanner;
		LoonScanner::Parser parser;
		//syntax table
		SymbolTable<std::string> strTable, idenTable;
		//root of AST tree
		NodeProgram* program;


		//Phase 3
		//function with decorated name 
		std::map<FunctionDeco, int> functionDeco;
		using Iter = decltype(functionDeco)::iterator;
		//function with decorated name, ordered in original name
		std::map<Symbol, std::vector<Iter>> functionDecoNameOrdered;
		//all types
		std::map<Symbol, int> types;
		void registerDefaultTypes();
		void functionDecoration();

		//common toolkits
		Errors errs;
		std::ostream& infoOut;
		std::ostream& lexSynOut;
		std::ostream& semOut;
		std::ostream& genOut;
		std::istream& cin;

	public:
		//cin of file path
		Compiler(std::istream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&);
		//Phase 1 & 2
		bool lexicalAndSyntaxAnalysis();
		//Phase 3
		bool semanticAnalysis(int);
		//Integrated all phases into one function
		bool parse();
	};
}


