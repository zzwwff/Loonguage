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
		public std::vector<std::shared_ptr<NodeSentence>>,
		public Node
	{
	public:
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		NodeSentences(std::shared_ptr<NodeSentence>);
		NodeSentences(int);
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeSExpr :
		public NodeSentence
	{
		std::shared_ptr<NodeExpr> expr;
	public:
		NodeSExpr(std::shared_ptr<NodeExpr>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeSIf :
		public NodeSentence
	{
		std::shared_ptr<NodeExpr> predicate;
		std::shared_ptr<NodeSentence> sentence;
	public:
		NodeSIf(std::shared_ptr<NodeExpr>, std::shared_ptr<NodeSentence>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeSWhile :
		public NodeSentence
	{
		std::shared_ptr<NodeExpr> predicate;
		std::shared_ptr<NodeSentence> sentence;
	public:
		NodeSWhile(std::shared_ptr<NodeExpr>, std::shared_ptr<NodeSentence>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeSBlock :
		public NodeSentence
	{
		std::shared_ptr<NodeSentences> sentences;
	public:
		NodeSBlock(std::shared_ptr<NodeSentences>);
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
		std::shared_ptr<NodeExpr> expr;
	public:
		NodeSDecl(TokenIden, TokenIden, std::shared_ptr<NodeExpr>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;

		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeSDeclArray :
		public NodeSentence
	{
		TokenIden type;
		TokenIden name;
		TokenInt size;
		Symbol nameDeco;
	public:
		NodeSDeclArray(TokenIden, TokenIden, TokenInt);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;

		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeSReturn :
		public NodeSentence
	{
		std::shared_ptr<NodeExpr> expr;
		NodeFunction* pfunction;
	public:
		NodeSReturn(int);
		NodeSReturn(std::shared_ptr<NodeExpr>);
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
