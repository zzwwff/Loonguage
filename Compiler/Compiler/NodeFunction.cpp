#include "NodeFunction.h"
namespace Loonguage {
	NodeFunction::NodeFunction(TokenIden rt, TokenIden n, NodeActuals* a, NodeSentence* s) :
		Node(rt.line, Node::NdFunction), returnType(rt), name(n), actuals(a), sentence(s)
	{
	}
	void NodeFunction::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeFunction (Return Type: " << returnType.getString()
			<< ", Name: " << name.getString() << ")" << std::endl;
		actuals->dump(cout, indent + 2);
		sentence->dump(cout, indent + 2);
	}
	void NodeFunctions::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeFunctions (Size:" << size()
			<< ")" << std::endl;
		for (const auto ac : *this)
			ac->dump(cout, indent + 2);
	}
	NodeFunctions::NodeFunctions(NodeFunction* f):
		Node(f->getLine(), Node::NdFormals)
	{
		push_back(f);
	}
}
