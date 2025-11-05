#include "FunctionDeco.h"
namespace Loonguage {
	FunctionDeco::FunctionDeco(NodeFunction* f):
		function(f)
	{
		name = function->name.value;
		returnType = function->returnType.value;
		nameDeco += name.getString();
		for (const auto& para : *(function->formals))
		{
			paramType.push_back(para->type.value);
			paramName.push_back(para->name.value);
			nameDeco.push_back('@');
			nameDeco += para->type.value.getString();
		}
	}
	bool FunctionDeco::operator<(const FunctionDeco& f) const
	{
		return nameDeco < f.nameDeco;
	}
}
