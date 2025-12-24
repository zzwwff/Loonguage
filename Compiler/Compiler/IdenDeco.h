#pragma once
#include "SymbolTable.h"

namespace Loonguage {
	class IdenDeco
	{
		using Symbol = SymbolTable<std::string>::Symbol;
	public:
		Symbol name;
		Symbol type;
		Symbol nameDeco;
		bool operator < (const IdenDeco&) const;
		IdenDeco(Symbol n, Symbol t, std::map<std::string, int>&);
		IdenDeco() {}
	};

}

