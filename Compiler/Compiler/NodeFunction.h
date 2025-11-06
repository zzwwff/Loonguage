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
		void dumpAST(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};

	class NodeFunctions :
		public std::vector<NodeFunction*>, 
		public Node
	{
	public:
		void dumpAST(std::ostream&, int) const;
		NodeFunctions(NodeFunction*);
		NodeFunctions(int);
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};
}
