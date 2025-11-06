#include "FunctionDeco.h"
#include "NodeFunction.h"

namespace Loonguage {
	FunctionDeco::FunctionDeco(NodeFunction* f):
		function(f)
	{
		std::string str;
		name = function->name.value;
		returnType = function->returnType.value;
		str += name.getString();
		for (const auto& para : *(function->formals))
		{
			paramType.push_back(para->type.value);
			paramName.push_back(para->name.value);
			str.push_back('@');
			str += para->type.value.getString();
		}
		nameDeco = name.getPointer()->addSymbol(str);
	}
	bool FunctionDeco::operator<(const FunctionDeco& f) const
	{
		return nameDeco < f.nameDeco;
	}
}
