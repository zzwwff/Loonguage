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
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);

	};

	class NodeSentences :
		public std::vector<NodeSentence*>,
		public Node
	{
	public:
		void dumpAST(std::ostream&, int) const;
		NodeSentences(NodeSentence*);
		NodeSentences(int);
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);

	};

	class NodeSExpr :
		public NodeSentence
	{
		NodeExpr* expr;
	public:
		NodeSExpr(NodeExpr*);
		void dumpAST(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);

	};

	class NodeSIf :
		public NodeSentence
	{
		NodeExpr* predicate;
		NodeSentence* sentence;
	public:
		NodeSIf(NodeExpr*, NodeSentence*);
		void dumpAST(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);

	};

	class NodeSWhile :
		public NodeSentence
	{
		NodeExpr* predicate;
		NodeSentence* sentence;
	public:
		NodeSWhile(NodeExpr*, NodeSentence*);
		void dumpAST(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};

	class NodeSBlock :
		public NodeSentence
	{
		NodeSentences* sentences;
	public:
		NodeSBlock(NodeSentences*);
		void dumpAST(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);

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
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);

	};

	class NodeSReturn :
		public NodeSentence
	{
		NodeExpr* expr;
		NodeFunction* pfunction;
	public:
		NodeSReturn(NodeExpr*);
		void dumpAST(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};

	class NodeSContinue :
		public NodeSentence
	{
		NodeWhile* pwhile;
	public:
		NodeSContinue(int);
		void dumpAST(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};

	class NodeSBreak :
		public NodeSentence
	{
		NodeWhile* pwhile;
	public:
		NodeSBreak(int);
		void dumpAST(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, Symbol>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};
}
