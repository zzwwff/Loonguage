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

	void NodeProgram::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeProgram" << std::endl;
		if (functions != NULL)
			functions->dumpAST(cout, indent + 2);
	}

	void NodeProgram::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeProgram" << std::endl;
		if (functions != NULL)
			functions->dumpSem(cout, indent + 2);
	}

	void NodeProgram::annotateType(std::map<std::string, int>& numOfSymbol,
							std::map<Symbol, IdenDeco>& nameOfSymbol, 
							const FunctionMapNameOrdered& functionMap, 
							SemanticContext context, Errors& errs)
	{
		
		functions->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
	}
}

