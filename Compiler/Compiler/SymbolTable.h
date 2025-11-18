#pragma once
#include <map>
#include <cstring>
#include <string>
#include <iterator>
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
		SymbolTable<T>* getPointer() const {
			return pointer;
		}
        int getId() const
        {
            return id;
        }

        Symbol_(int i, SymbolTable<T>* p) :
            id(i), pointer(p)
        {
        }

		Symbol_() : id(0), pointer(NULL) {};
		//no matter whether REAL_NAME defined, getString() will be defined
		//that's no the case in SymbolTable
        T getString() const
        {
            return pointer->getString(id);
        }

		bool same(T t) const {
			if (*this == pointer->wrongType)
				return true;
			if (!pointer->exist(t))
				return false;
			return (*pointer)[t] == *this;
		}
		Symbol_ getWrongType() const {
			return pointer->wrongType;
		}
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
		Symbol wrongType;
		SymbolTable() = default;

		Symbol operator [] (const T& t) {
			return Symbol(m.at(t), this);
		}
		Symbol addSymbol(const T& t);
		bool exist(const T& t) const;

#ifdef REAL_NAME
		T getString(int) const;
#endif // REAL_NAME

		typename std::map<T, int>::iterator begin() { return m.begin(); }
		typename std::map<T, int>::iterator end() { return m.end(); }
	};

	//template class SymbolTable<std::string>;

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



#ifdef REAL_NAME
    template<typename T>
    T SymbolTable<T>::getString(int s) const
    {
        return revM.at(s);
    }



#else // REAL_NAME

    template<typename T>
    inline T Symbol_<T>::getString() const
    {
        return std::to_string(id);
    }

#endif


};



