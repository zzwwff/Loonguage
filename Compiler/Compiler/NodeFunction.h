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
	public:
		TokenIden returnType;
		TokenIden name;
		Symbol nameDeco;
		std::shared_ptr<NodeFormals> formals;
		std::shared_ptr<NodeSentence> sentence;
		std::vector<std::pair<Symbol, int>> locals;
		NodeFunction(TokenIden, TokenIden, std::shared_ptr<NodeFormals>, std::shared_ptr<NodeSentence>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeFunctions :
		public std::vector<std::shared_ptr<NodeFunction>>,
		public Node
	{
	public:
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		NodeFunctions(std::shared_ptr<NodeFunction>);
		NodeFunctions(int);
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	//for built-in functions made by Loonguage designer
	class NodeNativeFunction :
		public NodeFunction
	{
	public:
		NodeNativeFunction(TokenIden, TokenIden, std::shared_ptr<NodeFormals>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
        void builtInCodeGen(CodeGenContext&, std::vector<Code>&);
	};
}
