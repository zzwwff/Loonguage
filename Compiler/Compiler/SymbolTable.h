#pragma once
#include <map>
#include <cstring>
#include <string>
#include "GeneralSetting.h"
namespace Loonguage {
	template<typename T> 
		class SymbolTable;


	template<typename T>
	class Symbol_ {
		int id;
		SymbolTable<T>* pointer;
	public:
		bool operator < (const Symbol_& s) const;
		int getId() const;
		Symbol_(int, SymbolTable<T>*);
		Symbol_() : id(0), pointer(NULL) {};
		T getString() const;
	};

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

		Symbol operator [] (const T& t) const;
		Symbol addSymbol(const T& t);
		bool exist(const T& t) const;

#ifdef REAL_NAME
		T getString(int) const;
#endif // REAL_NAME


	};

	extern SymbolTable<std::string> strTable, idenTable;
};



