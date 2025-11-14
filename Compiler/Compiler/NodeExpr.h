#pragma once
#include "Node.h"
#include "TokenIden.h"
#include "NodeActual.h"
#include "TokenInt.h"
#include "TokenString.h"
#include "SymbolTable.h"
namespace Loonguage {
	class NodeExpr :
		public Node
	{
	public:
		using Symbol = SymbolTable<std::string>::Symbol;
		Symbol type;
	public:
		Symbol getType() const;
		NodeExpr(int, Node::NodeType);
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};

	class NodeEIden :
		public NodeExpr
	{
		TokenIden iden;
		Symbol idenDeco;
	public:
		NodeEIden(TokenIden);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeEBracket :
		public NodeExpr
	{
		std::shared_ptr<NodeExpr> expr;
	public:
		NodeEBracket(std::shared_ptr<NodeExpr>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeActuals;

	class NodeEDispatch :
		public NodeExpr
	{
		TokenIden iden;
		std::shared_ptr<NodeActuals> actuals;
		Symbol idenDeco;
	public:
		NodeEDispatch(TokenIden, std::shared_ptr<NodeActuals>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;

		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeECalc :
		public NodeExpr
	{
		std::shared_ptr<NodeExpr> expr1, expr2;
		char op;
	public:
		NodeECalc(std::shared_ptr<NodeExpr>, char, std::shared_ptr<NodeExpr>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeEEqua :
		public NodeExpr
	{
		std::shared_ptr<NodeExpr> expr1, expr2;
	public:
		NodeEEqua(std::shared_ptr<NodeExpr>, std::shared_ptr<NodeExpr>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeELess :
		public NodeExpr
	{
		std::shared_ptr<NodeExpr> expr1, expr2;
	public:
		NodeELess(std::shared_ptr<NodeExpr>, std::shared_ptr<NodeExpr>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeERev :
		public NodeExpr
	{
		std::shared_ptr<NodeExpr> expr;
	public:
		NodeERev(std::shared_ptr<NodeExpr>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeEAssign :
		public NodeExpr
	{
		TokenIden iden;
		Symbol idenDeco;
		std::shared_ptr<NodeExpr> expr;
	public:
		NodeEAssign(TokenIden, std::shared_ptr<NodeExpr>);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeEInt :
		public NodeExpr
	{
		TokenInt int_;
	public:
		NodeEInt(TokenInt);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeEStr :
		public NodeExpr
	{
		TokenString str;
	public:
		NodeEStr(TokenString);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
	};
}

