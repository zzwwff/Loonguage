#include "NodeExpr.h"
namespace Loonguage {
	NodeExpr::NodeExpr(int l, Node::NodeType t) :
		Node(l, t)
	{

	}

	NodeEIden::NodeEIden(TokenIden i):
		NodeExpr(i.line, Node::NdEIden), iden(i)
	{
	}

	void NodeEIden::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEIden (Name:" << iden.getString()
			<< ")" << std::endl;
	}

	NodeEBracket::NodeEBracket(NodeExpr* e):
		NodeExpr(e->getLine(), Node::NdEBracket), expr(e)
	{
	}

	void NodeEBracket::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << std::endl;
		expr->dump(cout, indent + 2);
	}

	NodeEDispatch::NodeEDispatch(TokenIden i, NodeActuals* a):
		NodeExpr(i.line, Node::NdEDispatch), iden(i), actuals(a)
	{
	}

	void NodeEDispatch::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEDispatch (Iden:" << iden.getString() << ")" << std::endl;
		actuals->dump(cout, indent + 2);
	}

	NodeECalc::NodeECalc(NodeExpr* e1, char c, NodeExpr* e2):
		NodeExpr(e1->getLine(), Node::NdECalc), expr1(e1), op(c), expr2(e2)
	{
	}

	void NodeECalc::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeECalc (Op:" << op << ")" << std::endl;
		expr1->dump(cout, indent + 2);
		expr2->dump(cout, indent + 2);
	}

	NodeEEqua::NodeEEqua(NodeExpr* e1, NodeExpr* e2):
		NodeExpr(e1->getLine(), Node::NdEEqua), expr1(e1), expr2(e2)
	{
	}

	void NodeEEqua::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEEqua" << std::endl;
		expr1->dump(cout, indent + 2);
		expr2->dump(cout, indent + 2);
	}

	NodeELess::NodeELess(NodeExpr* e1, NodeExpr* e2) :
		NodeExpr(e1->getLine(), Node::NdEEqua), expr1(e1), expr2(e2)
	{
	}

	void NodeELess::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeELess" << std::endl;
		expr1->dump(cout, indent + 2);
		expr2->dump(cout, indent + 2);
	}

	NodeERev::NodeERev(NodeExpr* e):
		NodeExpr(e->getLine(), Node::NdERev), expr(e)
	{
	}
	void NodeERev::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeERev" << std::endl;
		expr->dump(cout, indent + 2);
	}

	NodeEAssign::NodeEAssign(TokenIden i, NodeExpr* e):
		NodeExpr(i.line, Node::NdEAssign),  expr(e), iden(i)
	{
	}

	void NodeEAssign::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEAssign (Iden:" << iden.getString() << ")" << std::endl;
		expr->dump(cout, indent + 2);
	}

	NodeEInt::NodeEInt(TokenInt i):
		NodeExpr(i.line, Node::NdEInt), int_(i)
	{
	}

	void NodeEInt::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEInt (Value:" << int_.getValue() << ")" << std::endl;
	}

	NodeEStr::NodeEStr(TokenString s):
		NodeExpr(s.line, Node::NdEStr), str(s)
	{
	}
	void NodeEStr::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEStr (Value:\"" << str.getValue() << "\")" << std::endl;
	}
}