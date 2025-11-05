#include "NodeFunction.h"
namespace Loonguage {
	NodeFunction::NodeFunction(TokenIden rt, TokenIden n, NodeFormals* a, NodeSentence* s) :
		Node(rt.line, Node::NdFunction), returnType(rt), name(n), formals(a), sentence(s)
	{
	}
	void NodeFunction::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeFunction (Return Type: " << returnType.getString()
			<< ", Name: " << name.getString() << ")" << std::endl;
		formals->dump(cout, indent + 2);
		sentence->dump(cout, indent + 2);
	}

	std::vector<SymbolTable<std::string>::Symbol> NodeFunction::getSignature() const
	{
		std::vector<SymbolTable<std::string>::Symbol> vec;
		vec.push_back(returnType.value);
		for (auto formal : *formals)
			vec.push_back(formal->name.value);
		return vec;
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

	NodeFunctions::NodeFunctions(int l):
		Node(l, Node::NdFormals)
	{
	}
}
