#pragma once
#include "SymbolTable.h"
namespace Loonguage {
	class NodeFunction;
	class NodeWhile;


	class SemanticContext
	{
	public:
		SymbolTable<std::string>::Symbol returnType;
		NodeFunction* pfunction;
		NodeWhile* pwhile;
	};
}


