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
		NodeExpr* expr;
	public:
		NodeEBracket(NodeExpr*);
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
		NodeActuals* actuals;
		Symbol idenDeco;
	public:
		NodeEDispatch(TokenIden, NodeActuals*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;

		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeECalc :
		public NodeExpr
	{
		NodeExpr* expr1, *expr2;
		char op;
	public:
		NodeECalc(NodeExpr*, char, NodeExpr*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeEEqua :
		public NodeExpr
	{
		NodeExpr* expr1, * expr2;
	public:
		NodeEEqua(NodeExpr*, NodeExpr*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);
	};

	class NodeELess :
		public NodeExpr
	{
		NodeExpr* expr1, * expr2;
	public:
		NodeELess(NodeExpr*, NodeExpr*);
		void dumpAST(std::ostream&, int) const;
		void dumpSem(std::ostream&, int) const;
		void annotateType(std::map<std::string, int>&, std::map<Symbol, IdenDeco>&, const FunctionMapNameOrdered&, SemanticContext, Errors&);
		void codeGen(CodeGenContext&, std::vector<Code>&);

	};

	class NodeERev :
		public NodeExpr
	{
		NodeExpr* expr;
	public:
		NodeERev(NodeExpr*);
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
		NodeExpr* expr;
	public:
		NodeEAssign(TokenIden, NodeExpr*);
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

