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
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};
}
