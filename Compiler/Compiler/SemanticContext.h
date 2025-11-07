#pragma once
#include "SymbolTable.h"
#include <map>
namespace Loonguage {
	class NodeFunction;
	class NodeSWhile;


	class SemanticContext
	{
	public:
		using Symbol = SymbolTable<std::string>::Symbol;
		Symbol returnType;
		NodeFunction* pfunction;
		NodeSWhile* pwhile;
		SymbolTable<std::string>* idenTable;
		std::map<Symbol, int>* types;
	};
}


