#include "IdenDeco.h"
namespace Loonguage {
	bool IdenDeco::operator<(const IdenDeco& deco) const
	{
		return nameDeco < deco.nameDeco;
	}
	IdenDeco::IdenDeco(Symbol n, Symbol t, std::map<std::string, int>& num) :
		name(n), type(t)
	{
		std::string nameTypeDeco = name.getString() + "@" + type.getString();
		int k = ++num[nameTypeDeco];
		std::string nameDecoStr = nameTypeDeco + "@" + std::to_string(k);
		nameDeco = n.getPointer()->addSymbol(nameDecoStr);
	}
}