#pragma once
#include <iostream>
#include <map>
#include "IdenDeco.h"
#include "SymbolTable.h"
#include "FunctionDeco.h"
#include "Error.h"
#include "SemanticContext.h"
#include "CodeGenContext.h"
#include "Code.h"
namespace Loonguage {
	class Node
	{
	public:
		enum NodeType {
			NdNoType,
			NdProgram,
			NdFunctions,
			NdFunction,
			NdFormal,
			NdFormals,
			NdSentences,
			NdSentence,
			NdSIf,
			NdSWhile,
			NdSBlock,
			NdSDecl,
			NdSExpr,
			NdSReturn,
			NdSContinue,
			NdSBreak,
			NdExpr,
			NdEIden,
			NdEBracket,
			NdEDispatch,
			NdECalc,
			NdEEqua,
			NdELess,
			NdERev,
			NdEAssign,
			NdEInt,
			NdActual,
			NdActuals,
			NdEStr,
		};
		using Symbol = SymbolTable<std::string>::Symbol;
		using FunctionMapNameOrdered = std::map<Symbol, std::vector<std::map<FunctionDeco, int>::iterator>>;
		using Reg = Register::Registers;

	protected:
		int line;
		NodeType type;
		void indent(std::ostream&, int) const;
	public:
		
		int getLine() const;
		Node(int l, NodeType nt);
		Node();
		virtual void dumpAST(std::ostream&, int) const;
		virtual void dumpSem(std::ostream&, int) const;

		virtual void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);

		virtual void codeGen(CodeGenContext&, std::vector<Code>&);
	};

};

