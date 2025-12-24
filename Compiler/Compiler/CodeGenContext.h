#pragma once
#include "Label.h"
#include "SymbolTable.h"
#include <map>
#include <memory>
namespace Loonguage {
	class CodeGenContext
	{
		using Symbol = SymbolTable<std::string>::Symbol;
	public:
		std::shared_ptr<LabelAllocator> allocator;
		std::map<Symbol, int> delta;
		std::map<Symbol, int> strPosition;
		int width;
		Label returnLabel;
		Label continueLabel;
		Label breakLabel;
	};


}
