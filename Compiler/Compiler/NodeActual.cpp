#include "NodeActual.h"


namespace Loonguage {
	NodeActual::NodeActual(NodeExpr* e) :
		Node(e->getLine(), Node::NdActual), expr(e)
	{
	}

	void NodeActual::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActual" << std::endl;
		expr->dump(cout, indent + 2);
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

	void NodeActuals::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActuals (Size:" << size()
			<< ")" << std::endl;
		for (const auto ac : *this)
			ac->dump(cout, indent + 2);
	}
}