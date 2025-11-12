#pragma once
#include "Label.h"
#include "SymbolTable.h"
#include <map>
namespace Loonguage {
	class CodeGenContext
	{
		using Symbol = SymbolTable<std::string>::Symbol;
	public:
		LabelAllocator* allocator;
		std::map<Symbol, int> delta;
		int width;
		Label returnLabel;
		Label continueLabel;
		Label breakLabel;
	};


}
