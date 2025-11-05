#include "NodeFormal.h"
namespace Loonguage {
	Loonguage::NodeFormal::NodeFormal(TokenIden t, TokenIden n) :
		Node(t.line, Node::NdFormal), type(t), name(n)
	{
	}
	void NodeFormal::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActual (Type:" << type.getString() 
			<< ", Name: " << name.getString() << ")" << std::endl;
	}
	void NodeFormals::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActuals (Size:" << size()
			<< ")" << std::endl;
		for (const auto ac : *this)
			ac->dump(cout, indent + 2);
	}
	NodeFormals::NodeFormals(NodeFormal* a):
		Node(a->getLine(), Node::NodeType::NdFormals)
	{
		push_back(a);
	}
	NodeFormals::NodeFormals(int l):
		Node(l, Node::NodeType::NdFormals)
	{
	}
}

