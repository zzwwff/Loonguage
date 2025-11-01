#pragma once
#include <map>
#include <cstring>
#include "GeneralSetting.h"
namespace Loonguage {
	template<typename T> 
		class SymbolTable;


	template<typename T>
	class Symbol_ {
		int id;
		SymbolTable<T>* pointer;
	public:
		int getId() const;
		Symbol_(int, SymbolTable<T>*);
		Symbol_() : id(0), pointer(NULL) {};
#ifdef REAL_NAME
		T getString() const;
#endif // REAL_NAME
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
		Symbol operator [] (const T& t) const;
		Symbol addSymbol(const T& t);
		bool exist(const T& t) const;

#ifdef REAL_NAME
		T getString(int) const;
#endif // REAL_NAME


	};

};



