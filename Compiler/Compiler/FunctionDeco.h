#pragma once
#include <string>
#include <vector>
#include "SymbolTable.h"

namespace Loonguage {
	class NodeFunction;

	class FunctionDeco
	{
		using Symbol = SymbolTable<std::string>::Symbol;
	public:
		Symbol name;
		Symbol returnType;
		std::vector<Symbol> paramType;
		std::vector<Symbol> paramName;
		NodeFunction* function;
		Symbol nameDeco;
		FunctionDeco(NodeFunction*);

		bool operator < (const FunctionDeco& f) const;
	};


}
