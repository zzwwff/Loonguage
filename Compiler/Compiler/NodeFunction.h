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
		Symbol nameDeco;
		NodeFormals* formals;
		NodeSentence* sentence;
		NodeFunction(TokenIden, TokenIden, NodeFormals*, NodeSentence*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeFunctions :
		public std::vector<NodeFunction*>, 
		public Node
	{
	public:
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		NodeFunctions(NodeFunction*);
		NodeFunctions(int);
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};
}
