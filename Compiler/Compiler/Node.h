#pragma once
#include <iostream>
namespace Loonguage {
	enum NodeType {
		NodeNoType,
		NodeProgram,
		NodeFunctions,
		NodeFunction,
		NodeFormal,
		NodeFormals,
		NodeSentences,
		NodeSentence,
		NodeExpr,
		NodeEIden,
		NodeEBracket,
		NodeEDispatch,
		NodeECalc,
		NodeEComp,
		NodeELess,
		NodeERev,
		NodeEAssign,
		NodeEInt,
		NodeActual,
		NodeActuals
	};
	class Node
	{
		int line;
		NodeType type;
		void indent(std::ostream&, int) const;
	public:
		Node(int l, NodeType nt);
		Node();
		void dump(std::ostream&, int) const;
	};

};

