#include "NodeFunction.h"
namespace Loonguage {
	NodeFunction::NodeFunction(TokenIden rt, TokenIden n, NodeFormals* a, NodeSentence* s) :
		Node(rt.line, Node::NdFunction), returnType(rt), name(n), formals(a), sentence(s)
	{
	}
	void NodeFunction::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeFunction (Return Type: " << returnType.getString()
			<< ", Name: " << name.getString() << ")" << std::endl;
		formals->dumpAST(cout, indent + 2);
		sentence->dumpAST(cout, indent + 2);
	}

	void NodeFunction::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeFunction (Return Type: " << returnType.getString()
			<< ", NameDeco: " << nameDeco.getString() << ")" << std::endl;
		formals->dumpSem(cout, indent + 2);
		sentence->dumpSem(cout, indent + 2);
	}


	void NodeFunction::annotateType(std::map<std::string, int>& numOfSymbol,
									std::map<Symbol, IdenDeco>& nameOfSymbol, 
									const FunctionMapNameOrdered& functionMap, 
									SemanticContext context, Errors& errs)
	{
		std::map<Symbol, IdenDeco> currentNameOfSymbol = nameOfSymbol;
		//add all the formals
		for (auto formal : *formals)
		{
			//step 1: get name@type@id
			//we can make sure that type is valid because it is checked in Compiler::functionDecoration
			Symbol name = formal->name.value;
			Symbol type = formal->type.value;
			IdenDeco deco = IdenDeco(name, type, numOfSymbol);
			//step 2: load nameDeco into formal and currentNameOfSymbol
			formal->nameDeco = deco.nameDeco;
			currentNameOfSymbol[name] = deco;
		}
		//update context
		context.pfunction = this;
		context.returnType = returnType.value;
		//call annotateType inside the function body
		sentence->annotateType(numOfSymbol, currentNameOfSymbol, functionMap, context, errs);
	}



	void NodeFunctions::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeFunctions (Size:" << size()
			<< ")" << std::endl;
		for (const auto ac : *this)
			ac->dumpAST(cout, indent + 2);
	}

	void NodeFunctions::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeFunctions (Size:" << size()
			<< ")" << std::endl;
		for (const auto ac : *this)
			ac->dumpSem(cout, indent + 2);
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

	void NodeFunctions::annotateType(std::map<std::string, int>& numOfSymbol,
									 std::map<Symbol, IdenDeco>& nameOfSymbol, 
									 const FunctionMapNameOrdered& functionMap, 
									 SemanticContext context, Errors& errs)
	{
		//just call function
		//formal will be added in function::annotateType
		for (auto function : *this)
			function->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
	}
}
