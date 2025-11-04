#include "NodeProgram.h"
namespace Loonguage {
	NodeProgram::NodeProgram():
		Node(0, Node::NdProgram), functions(NULL)
	{
	}

	NodeProgram::NodeProgram(NodeFunctions* p) :
		Node(p->getLine(), Node::NdProgram), functions(p)
	{
	}
	void NodeProgram::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeProgram" << std::endl;
		if (functions != NULL)
			functions->dump(cout, indent + 2);
	}
}

