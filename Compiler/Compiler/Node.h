#pragma once
#include <iostream>
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
			NdEStr
		};

	protected:
		int line;
		NodeType type;
		void indent(std::ostream&, int) const;
	public:
		
		int getLine();
		Node(int l, NodeType nt);
		Node();
		virtual void dump(std::ostream&, int) const;
	};

};

