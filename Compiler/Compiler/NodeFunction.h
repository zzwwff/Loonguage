#pragma once
#include "Node.h"
#include "TokenIden.h"
#include "NodeFormal.h"
#include "NodeSentence.h"
#include "SymbolTable.h"
#include <vector>
namespace Loonguage {
	class NodeFunction :
		public Node
	{
	public:
		TokenIden returnType;
		TokenIden name;
		NodeFormals* formals;
		NodeSentence* sentence;
		NodeFunction(TokenIden, TokenIden, NodeFormals*, NodeSentence*);
		void dump(std::ostream&, int) const;
		std::vector<SymbolTable<std::string>::Symbol> getSignature() const;
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
