#include "NodeActual.h"


namespace Loonguage {
	NodeActual::NodeActual(NodeExpr* e) :
		Node(e->getLine(), Node::NdActual), expr(e)
	{
	}

	void NodeActual::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActual" << std::endl;
		expr->dumpAST(cout, indent + 2);
	}

	NodeActuals::NodeActuals(NodeActual* n) :
		Node(n->getLine(), Node::NdActuals)
	{
		push_back(n);
	}

	NodeActuals::NodeActuals(int l) :
		Node(l, Node::NdActuals)
	{
	}

	void NodeActuals::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActuals (Size:" << size()
			<< ")" << std::endl;
		for (const auto ac : *this)
			ac->dumpAST(cout, indent + 2);
	}
}