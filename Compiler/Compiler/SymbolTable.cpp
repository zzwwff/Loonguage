#include "SymbolTable.h"
#include <iostream>
namespace Loonguage{

	template<typename T>
	Symbol_<T>::Symbol_(int i, SymbolTable<T>* p) :
		id(i), pointer(p)
	{

	}

	//WATCH OUT!
	//some definitions are put in header, turn to SymbolTable.h for more detals

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

#else // REAL_NAME

	template<typename T>
	inline T Symbol_<T>::getString() const
	{
		return std::to_string(id);
	}

#endif


}


