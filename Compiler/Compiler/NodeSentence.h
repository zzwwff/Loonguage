#pragma once
#include "Node.h"
#include "TokenIden.h"
#include "NodeExpr.h"
#include "IdenDeco.h"
#include <vector>
namespace Loonguage {
	class NodeExpr;

	class NodeSentence :
		public Node
	{
	public:

		NodeSentence(int);
		NodeSentence(int, Node::NodeType);
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeSentences :
		public std::vector<NodeSentence*>,
		public Node
	{
	public:
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		NodeSentences(NodeSentence*);
		NodeSentences(int);
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeSExpr :
		public NodeSentence
	{
		NodeExpr* expr;
	public:
		NodeSExpr(NodeExpr*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeSIf :
		public NodeSentence
	{
		NodeExpr* predicate;
		NodeSentence* sentence;
	public:
		NodeSIf(NodeExpr*, NodeSentence*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeSWhile :
		public NodeSentence
	{
		NodeExpr* predicate;
		NodeSentence* sentence;
	public:
		NodeSWhile(NodeExpr*, NodeSentence*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeSBlock :
		public NodeSentence
	{
		NodeSentences* sentences;
	public:
		NodeSBlock(NodeSentences*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;

		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeSDecl :
		public NodeSentence
	{
		TokenIden type;
		TokenIden name;
		Symbol nameDeco;	
	public:
		NodeSDecl(TokenIden, TokenIden);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;

		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		//no codeGen
	};

	class NodeSReturn :
		public NodeSentence
	{
		NodeExpr* expr;
		NodeFunction* pfunction;
	public:
		NodeSReturn(int);
		NodeSReturn(NodeExpr*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;

		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeSContinue :
		public NodeSentence
	{
		NodeSWhile* pwhile;
	public:
		NodeSContinue(int);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;

		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeSBreak :
		public NodeSentence
	{
		NodeSWhile* pwhile;
	public:
		NodeSBreak(int);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};
}
