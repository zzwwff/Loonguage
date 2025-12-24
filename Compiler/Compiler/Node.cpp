#include "Node.h"


namespace Loonguage {
	int Node::LIFE = 0;

	void Node::indent(std::ostream& cout, int ind) const
	{
		for (int i = 1; i <= ind; i++)
			cout << ' ';
	}

	int Node::getLine() const
	{
		return line;
	}

	Node::Node(int l, NodeType nt):
		line(l), type(nt)
	{
		LIFE++;
	}

	Node::Node():
		line(0), type(NdNoType)
	{
		LIFE++;
	}

	Node::~Node()
	{
		LIFE--;
	}

	void Node::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": Node" << std::endl;
	}

	void Node::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": Node" << std::endl;
	}

	void Node::annotateType(std::map<std::string, int>& numOfSymbol, 
							std::map<Symbol, IdenDeco>& nameOfSymbol, 
							const FunctionMapNameOrdered& functionMap, 
							SemanticContext context, Errors& errs)
	{
	}

	void Node::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
	}

}

