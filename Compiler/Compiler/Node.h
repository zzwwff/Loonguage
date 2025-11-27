#pragma once
#include <iostream>
#include <map>
#include <memory>
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
		//manage memory leak
		static int LIFE;
		enum NodeType {
			NdNoType,
			NdProgram,
			NdFunctions,
			NdFunction,
			NdFormal,
			NdFormals,
			NdSentences,
			NdSentence,
			NdNativeFunction,
			NdSIf,
			NdSWhile,
			NdSBlock,
			NdSDecl,
			NdSDeclArray,
			NdSExpr,
			NdSReturn,
			NdSContinue,
			NdSBreak,
			NdExpr,
			NdEIden,
			NdEIdenArray,
			NdEBracket,
			NdEDispatch,
			NdECalc,
			NdEEqua,
			NdELess,
			NdERev,
			NdEAssign,
			NdEAssignArray,
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
		void indent(std::ostream&, int) const;
	public:
		NodeType type;
		int getLine() const;
		Node(int l, NodeType nt);
		Node();
		~Node();
		virtual void dumpAST(std::ostream&, int) const;
		virtual void dumpSem(std::ostream&, int) const;

		virtual void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);

		virtual void codeGen(CodeGenContext&, std::vector<Code>&);
	};

};

