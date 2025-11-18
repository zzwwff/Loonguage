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

	//Compiler is memory-safe
	class Compiler
	{
		using Symbol = SymbolTable<std::string>::Symbol;
		//Phase 0 
		//Preprocess, add some built-in function
		//Phase 1 ~ 2
		//for lexical and syntax analysis
		LoonScanner::Scanner scanner;
		LoonScanner::Parser parser;
		LoonScanner::location loc;
    public:
		//syntax table
		SymbolTable<std::string> strTable, idenTable;
    private:
		//root of AST tree
		std::shared_ptr<NodeProgram> program;


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
        //whether is it able to run
        bool runable;
        //Phase 4
        //code generation
        std::vector<Code> codes;
		std::map<Symbol, int> strPosition;
		void allocateString();

        //cin of file path
		Compiler(std::istream&, std::ostream&, std::ostream&, std::ostream&, std::ostream&);
		Compiler(std::string, std::ostream&, std::ostream&, std::ostream&, std::ostream&);
		//Phase 1 & 2
		bool lexicalAndSyntaxAnalysis();
		//Phase 3
		bool semanticAnalysis(int);
		//Phase 4
		bool codeGeneration();
		//Integrated all phases into one function
		bool parse();
	};
}


