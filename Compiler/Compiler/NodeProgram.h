#pragma once
#include "Node.h"
#include "NodeFunction.h"
namespace Loonguage {
	class NodeProgram:
		public Node
	{
	public:
		NodeFunctions* functions;
		NodeProgram();
		NodeProgram(NodeFunctions*);
		void dumpAST(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};
}
