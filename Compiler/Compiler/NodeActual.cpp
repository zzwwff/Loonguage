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

	void NodeActual::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActual" << std::endl;
		expr->dumpSem(cout, indent + 2);
	}


	void NodeActual::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		type = expr->type;
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
	void NodeActuals::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeActuals (Size:" << size()
			<< ")" << std::endl;
		for (const auto ac : *this)
			ac->dumpSem(cout, indent + 2);
	}

	void NodeActuals::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		for (auto actual : *this)
			actual->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
	}
}