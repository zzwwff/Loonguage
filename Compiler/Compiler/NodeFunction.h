#pragma once
#include "Node.h"
#include "TokenIden.h"
#include "NodeFormal.h"
#include "NodeSentence.h"
#include <vector>
namespace Loonguage {
	class NodeFunction :
		public Node
	{
		TokenIden returnType;
		TokenIden name;
		NodeFormals* formals;
		NodeSentence* sentence;
	public:
		NodeFunction(TokenIden, TokenIden, NodeFormals*, NodeSentence*);
		void dump(std::ostream&, int) const;
	};

	class NodeFunctions :
		public std::vector<NodeFunction*>, 
		public Node
	{
	public:
		void dump(std::ostream&, int) const;
		NodeFunctions(NodeFunction*);
		NodeFunctions(int);
	};
}
