#include "NodeActual.h"
namespace Loonguage {
	Loonguage::NodeActual::NodeActual(TokenIden t, TokenIden n) :
		Node(t.line, Node::NdActual), type(t), name(n)
	{
	}
	void NodeActual::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActual (Type:" << type.getString() 
			<< ", Name: " << name.getString() << ")" << std::endl;
	}
	void NodeActuals::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActuals (Size:" << size()
			<< ")" << std::endl;
		for (const auto ac : *this)
			ac->dump(cout, indent + 2);
	}
	NodeActuals::NodeActuals(NodeActual* a):
		Node(a->getLine(), Node::NodeType::NdActuals)
	{
		push_back(a);
	}
}

