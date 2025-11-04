#pragma once
#include "Node.h"
#include "TokenIden.h"
#include "NodeActual.h"
#include "NodeSentence.h"
#include <vector>
namespace Loonguage {
	class NodeFunction :
		public Node
	{
		TokenIden returnType;
		TokenIden name;
		NodeActuals* actuals;
		NodeSentence* sentence;
	public:
		NodeFunction(TokenIden, TokenIden, NodeActuals*, NodeSentence*);
		void dump(std::ostream&, int) const;
	};

	class NodeFunctions :
		public std::vector<NodeFunction*>, 
		public Node
	{
	public:
		void dump(std::ostream&, int) const;
		NodeFunctions(NodeFunction*);
	};
}
