#include "NodeSentence.h"
namespace Loonguage
{
	NodeSentence::NodeSentence(int i):
		Node(i, Node::NdSentence)
	{
	}
	NodeSentence::NodeSentence(int i, Node::NodeType t):
		Node(i, t)
	{
	}

	void NodeSentence::annotateType(std::map<std::string, int>& numOfSymbol,
									std::map<Symbol, Symbol>& nameOfSymbol,
									const FunctionMapNameOrdered& functionMap,
									SemanticContext context, Errors& errs)
	{

	}

	NodeSIf::NodeSIf(NodeExpr* e, NodeSentence* s) :
		NodeSentence(e->getLine(), Node::NdSIf), predicate(e), sentence(s)
	{
	}

	void NodeSIf::annotateType(std::map<std::string, int>& numOfSymbol,
							   std::map<Symbol, Symbol>& nameOfSymbol,
							   const FunctionMapNameOrdered& functionMap,
							   SemanticContext context, Errors& errs)
	{
		predicate->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		sentence->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		Symbol pt = predicate->getType();
		if (!pt.same("int"))
			errs.push_back(Error("Semantic Analysis",
								getLine(),
								"Return type of the predicate in \"if\" shou be \"int\", not \"" + pt.getString() + "\"."));
	}

	void NodeSIf::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSIf" << std::endl;
		predicate->dumpAST(cout, indent + 2);
		sentence->dumpAST(cout, indent + 2);
	}

	NodeSWhile::NodeSWhile(NodeExpr* e, NodeSentence* s) :
		NodeSentence(e->getLine(), Node::NdSWhile), predicate(e), sentence(s)
	{
	}

	void NodeSWhile::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSWhile" << std::endl;
		predicate->dumpAST(cout, indent + 2);
		sentence->dumpAST(cout, indent + 2);
	}

	void NodeSWhile::annotateType(std::map<std::string, int>& numOfSymbol,
								  std::map<Symbol, Symbol>& nameOfSymbol,
								  const FunctionMapNameOrdered& functionMap,
								  SemanticContext context, Errors& errs)
	{
		predicate->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		sentence->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		Symbol pt = predicate->getType();
		if (!pt.same("int"))
			errs.push_back(Error("Semantic Analysis",
				getLine(),
				"Return type of the predicate in \"while\" shou be \"int\", not \"" + pt.getString() + "\"."));
	}


	NodeSBlock::NodeSBlock(NodeSentences* s):
		NodeSentence(s->getLine(), Node::NdSBlock), sentences(s)
	{
	}

	void NodeSBlock::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSBlock" << std::endl;
		sentences->dumpAST(cout, indent + 2);
	}

	void NodeSBlock::annotateType(std::map<std::string, int>& numOfSymbol,
								  std::map<Symbol, Symbol>& nameOfSymbol,
								  const FunctionMapNameOrdered& functionMap,
								  SemanticContext context, Errors& errs)
	{
		//inside a block is a new scope
		//so have to set new nameOfSymbol context
		std::map<Symbol, Symbol>& currentNameOfSymbol = nameOfSymbol;
		sentences->annotateType(numOfSymbol, currentNameOfSymbol, functionMap, context, errs);
	}

	NodeSDecl::NodeSDecl(TokenIden t, TokenIden n):
		NodeSentence(t.line, Node::NdSDecl), type(t), name(n)
	{
	}
	void NodeSDecl::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSDecl (Type: " << type.getString()
			<< ", Name: " << name.getString() << ")" << std::endl;
	}

	void NodeSDecl::annotateType(std::map<std::string, int>& numOfSymbol,
								 std::map<Symbol, Symbol>& nameOfSymbol,
								 const FunctionMapNameOrdered& functionMap,
								 SemanticContext context, Errors& errs)
	{
		//step 1: get name@type@id
		Symbol name = this->name.value;
		Symbol type = this->type.value;
		//decide whether type is valid
		if (functionMap.find(type) == functionMap.end())
			errs.push_back(Error("", getLine(),
				"Unknown type \"" + type.getString() + "\" of variable \"" + name.getString() + "\"."));
		else
		{
			//if type is valid...
			IdenDeco deco = IdenDeco(name, type, numOfSymbol);
			//step 2: load nameDeco into nameOfSymbol
			nameDeco = deco.nameDeco;
			nameOfSymbol[name] = deco.nameDeco;
		}

	}

	void NodeSentences::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSentences (Size: " << size() << ")" << std::endl;
		for (const auto& e : *this)
			e->dumpAST(cout, indent + 2);
	}

	NodeSentences::NodeSentences(NodeSentence* s):
		Node(s->getLine(), Node::NdSentences)
	{
		push_back(s);
	}

	NodeSentences::NodeSentences(int l):
		Node(l, Node::NdSentences)
	{
	}

	void NodeSentences::annotateType(std::map<std::string, int>& numOfSymbol,
									std::map<Symbol, Symbol>& nameOfSymbol, 
									const FunctionMapNameOrdered& functionMap, 
									SemanticContext context, Errors& errs)
	{
		//be aware that all sentences in sentence are in one scope
		//so nameOfSymbol will be passed to lower nodes on AST tree
		for (auto sentence : *this)
			sentence->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
	}

	NodeSExpr::NodeSExpr(NodeExpr* e) :
		NodeSentence(e->getLine(), Node::NdSExpr), expr(e)
	{
	}

	void NodeSExpr::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSExpr" << std::endl;
		expr->dumpAST(cout, indent + 2);
	}

	void NodeSExpr::annotateType(std::map<std::string, int>& numOfSymbol,
									std::map<Symbol, Symbol>& nameOfSymbol, 
									const FunctionMapNameOrdered& functionMap, 
									SemanticContext context, Errors& errs)
	{
		expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
	}

	NodeSReturn::NodeSReturn(NodeExpr* e) :
		NodeSentence(e->getLine(), Node::NdSReturn), expr(e), pfunction(NULL)
	{
	}

	void NodeSReturn::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSReturn" << std::endl;
		expr->dumpAST(cout, indent + 2);
	}

	void NodeSReturn::annotateType(std::map<std::string, int>& numOfSymbol,
								   std::map<Symbol, Symbol>& nameOfSymbol,
								   const FunctionMapNameOrdered& functionMap,
								   SemanticContext context, Errors& errs)
	{
		//check return type
		pfunction = context.pfunction;
		expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		Symbol ret = context.returnType;
		if (!(ret == expr->getType()))
		{
			errs.push_back(Error("", getLine(), 
				std::string("Return type \"") + expr->getType().getString() + 
				"\" does not match with definition \"" + ret.getString() + "\"."));
		}
	}

	NodeSContinue::NodeSContinue(int l) :
		NodeSentence(l, Node::NdSContinue), pwhile(NULL)
	{
	}

	void NodeSContinue::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSContinue" << std::endl;
	}

	void NodeSContinue::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, Symbol>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		//make sure continue is inside a loop and set pwhile
		if (context.pwhile == NULL)
			errs.push_back(Error("", getLine(),
				std::string("\"continue\" should be used inside a loop.")));
		else pwhile = context.pwhile;
	}

	NodeSBreak::NodeSBreak(int l) :
		NodeSentence(l, Node::NdSBreak), pwhile(NULL)
	{
	}

	void NodeSBreak::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSBreak" << std::endl;
	}

	void NodeSBreak::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, Symbol>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		//make sure continue is inside a loop and set pwhile
		if (context.pwhile == NULL)
			errs.push_back(Error("", getLine(),
				std::string("\"break\" should be used inside a loop.")));
		pwhile = context.pwhile;
	}
}

