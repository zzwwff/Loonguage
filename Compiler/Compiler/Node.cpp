#include "Node.h"

namespace Loonguage {
	void Node::indent(std::ostream& cout, int ind) const
	{
		for (int i = 1; i <= ind; i++)
			cout << ' ';
	}

	int Node::getLine()
	{
		return line;
	}

	Node::Node(int l, NodeType nt):
		line(l), type(nt)
	{
	}

	Node::Node():
		line(0), type(NdNoType)
	{
	}

	void Node::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": Node" << std::endl;
	}
}

