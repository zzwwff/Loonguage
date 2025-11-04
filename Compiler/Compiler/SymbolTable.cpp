#include "SymbolTable.h"
#include <iostream>
namespace Loonguage{
	template<typename T>
	SymbolTable<T>::SymbolTable()
	{
	}


	template<typename T>
	inline Symbol_<T> SymbolTable<T>::operator[](const T& t) const
	{
		return Symbol(m.at(t), this);
	}

	template<typename T>
	Symbol_<T> SymbolTable<T>::addSymbol(const T& t)
	{
		if (exist(t))
			return Symbol(m[t], this);
		Symbol s = Symbol(m.size(), this);
		m[t] = s.getId();
#ifdef REAL_NAME
		revM[s.getId()] = t;
#endif // REAL_NAME

		return s;
	}

	template<typename T>
	bool SymbolTable<T>::exist(const T& t) const
	{
		return m.find(t) != m.end();
	}

	template<typename T>
	inline int Symbol_<T>::getId() const
	{
		return id;
	}

	template<typename T>
	Symbol_<T>::Symbol_(int i, SymbolTable<T>* p) :
		id(i), pointer(p)
	{

	}

#ifdef REAL_NAME
	template<typename T>
	T SymbolTable<T>::getString(int s) const
	{
		return revM.at(s);
	}



	template<typename T>
	inline T Symbol_<T>::getString() const
	{
		return pointer->getString(id);
	}

#endif // REAL_NAME


}


