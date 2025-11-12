#pragma once
#include <vector>
#include "NodeExpr.h"
#include "Node.h"
namespace Loonguage {
	class NodeExpr;

	class NodeActual :
		public Node
	{
		NodeExpr* expr;
	public:
		Symbol type;
		NodeActual(NodeExpr*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeActuals :
		public std::vector<NodeActual*>,
		public Node
	{
	public:
		NodeActuals(NodeActual*);
		NodeActuals(int);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};
}

