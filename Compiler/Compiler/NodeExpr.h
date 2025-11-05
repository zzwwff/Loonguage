#pragma once
#include "Node.h"
#include "TokenIden.h"
#include "NodeActual.h"
#include "TokenInt.h"
#include "TokenString.h"
namespace Loonguage {
	class NodeExpr :
		public Node
	{
	public:
		NodeExpr(int, Node::NodeType);
	};

	class NodeEIden :
		public NodeExpr
	{
		TokenIden iden;
	public:
		NodeEIden(TokenIden);
		void dump(std::ostream&, int) const;
	};

	class NodeEBracket :
		public NodeExpr
	{
		NodeExpr* expr;
	public:
		NodeEBracket(NodeExpr*);
		void dump(std::ostream&, int) const;
	};

	class NodeActuals;

	class NodeEDispatch :
		public NodeExpr
	{
		TokenIden iden;
		NodeActuals* actuals;
	public:
		NodeEDispatch(TokenIden, NodeActuals*);
		void dump(std::ostream&, int) const;
	};

	class NodeECalc :
		public NodeExpr
	{
		NodeExpr* expr1, *expr2;
		char op;
	public:
		NodeECalc(NodeExpr*, char, NodeExpr*);
		void dump(std::ostream&, int) const;
	};

	class NodeEEqua :
		public NodeExpr
	{
		NodeExpr* expr1, * expr2;
	public:
		NodeEEqua(NodeExpr*, NodeExpr*);
		void dump(std::ostream&, int) const;
	};

	class NodeELess :
		public NodeExpr
	{
		NodeExpr* expr1, * expr2;
	public:
		NodeELess(NodeExpr*, NodeExpr*);
		void dump(std::ostream&, int) const;
	};

	class NodeERev :
		public NodeExpr
	{
		NodeExpr* expr;
	public:
		NodeERev(NodeExpr*);
		void dump(std::ostream&, int) const;
	};

	class NodeEAssign :
		public NodeExpr
	{
		TokenIden iden;
		NodeExpr* expr;
	public:
		NodeEAssign(TokenIden, NodeExpr*);
		void dump(std::ostream&, int) const;
	};

	class NodeEInt :
		public NodeExpr
	{
		TokenInt int_;
	public:
		NodeEInt(TokenInt);
		void dump(std::ostream&, int) const;
	};

	class NodeEStr :
		public NodeExpr
	{
		TokenString str;
	public:
		NodeEStr(TokenString);
		void dump(std::ostream&, int) const;
	};
}

