#pragma once
#include <map>
#include <cstring>
#include <string>
#include "GeneralSetting.h"
namespace Loonguage {
	template<typename T> 
		class SymbolTable;


	//declaration and definition of some particular functions in template class have to be put together in header file
	//otherwise linker will throw numerous errors
	//maybe can be handled future
	//https://blog.csdn.net/chigusakawada/article/details/78752668 for detail

	template<typename T>
	class Symbol_ {
		int id;
		SymbolTable<T>* pointer;
	public:
		bool operator < (const Symbol_& s) const {
			return id < s.id;
		}
		bool operator == (const Symbol_& s) const {
			return id == s.id && pointer == s.pointer;
		}
		int getId() const;
		Symbol_(int, SymbolTable<T>*);
		Symbol_() : id(0), pointer(NULL) {};
		//no matter whether REAL_NAME defined, getString() will be defined
		//that's no the case in SymbolTable
		T getString() const;
	};

	//template class SymbolTable<std::string>;


	template<typename T>
	class SymbolTable
	{
	public:
		using Symbol = Symbol_<T>;
	private:
		std::map<T, int> m;
#ifdef REAL_NAME
		std::map<int, T> revM;
#endif // REAL_NAME

	public:
		SymbolTable() = default;

		Symbol operator [] (const T& t) {
			return Symbol(m.at(t), this);
		}
		Symbol addSymbol(const T& t);
		bool exist(const T& t) const;

#ifdef REAL_NAME
		T getString(int) const;
#endif // REAL_NAME


	};

	//template class SymbolTable<std::string>;
};



