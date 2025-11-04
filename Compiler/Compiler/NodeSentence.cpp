#include "NodeSentence.h"
namespace Loonguage
{
	NodeSentence::NodeSentence(int i, Node::NodeType t):
		Node(i, t)
	{
	}

	NodeSIf::NodeSIf(NodeExpr* e, NodeSentence* s) :
		NodeSentence(e->getLine(), Node::NdSIf), predicate(e), sentence(s)
	{
	}

	void NodeSIf::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSIf" << std::endl;
		predicate->dump(cout, indent + 2);
		sentence->dump(cout, indent + 2);
	}

	NodeSWhile::NodeSWhile(NodeExpr* e, NodeSentence* s) :
		NodeSentence(e->getLine(), Node::NdSWhile), predicate(e), sentence(s)
	{
	}

	void NodeSWhile::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSWhile" << std::endl;
		predicate->dump(cout, indent + 2);
		sentence->dump(cout, indent + 2);
	}

	NodeSBlock::NodeSBlock(NodeSentences* s):
		NodeSentence(s->getLine(), Node::NdSBlock), sentences(s)
	{
	}

	void NodeSBlock::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSBlock" << std::endl;
		sentences->dump(cout, indent + 2);
	}

	NodeSDecl::NodeSDecl(TokenIden t, TokenIden n):
		NodeSentence(t.line, Node::NdSDecl), type(t), name(n)
	{
	}
	void NodeSDecl::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSDecl (Type: " << type.getString()
			<< ", Name: " << name.getString() << ")" << std::endl;
	}
	void NodeSentences::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSentences (Size: " << size() << ")" << std::endl;
		for (const auto& e : *this)
			e->dump(cout, indent + 2);
	}

	NodeSentences::NodeSentences(NodeSentence* s):
		Node(s->getLine(), Node::NdSentences)
	{
		push_back(s);
	}

	NodeSExpr::NodeSExpr(NodeExpr* e) :
		NodeSentence(e->getLine(), Node::NdSExpr), expr(e)
	{
	}

	void NodeSExpr::dump(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSExpr" << std::endl;
		expr->dump(cout, indent + 2);
	}
}

