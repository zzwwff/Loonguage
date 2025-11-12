#include "NodeSentence.h"
#include "NodeFunction.h"
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
									std::map<Symbol, IdenDeco>& nameOfSymbol,
									const FunctionMapNameOrdered& functionMap,
									SemanticContext context, Errors& errs)
	{

	}

	void NodeSentence::codeGen(CodeGenContext&, std::vector<Code>&)
	{
	}

	NodeSIf::NodeSIf(NodeExpr* e, NodeSentence* s) :
		NodeSentence(e->getLine(), Node::NdSIf), predicate(e), sentence(s)
	{
	}

	void NodeSIf::annotateType(std::map<std::string, int>& numOfSymbol,
							   std::map<Symbol, IdenDeco>& nameOfSymbol,
							   const FunctionMapNameOrdered& functionMap,
							   SemanticContext context, Errors& errs)
	{
		predicate->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		//if will start a new scope even though there's no block
		std::map<Symbol, IdenDeco> currentNameOfSymbol = nameOfSymbol;
		sentence->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		Symbol pt = predicate->getType();
		if (!pt.same("int"))
			errs.push_back(Error("Semantic Analysis",
								getLine(),
								"Return type of the predicate in \"if\" shou be \"int\", not \"" + pt.getString() + "\"."));
	}

	void NodeSIf::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		std::string endIf = std::string("endOfIf");
		Label endIfLabel(context.allocator->addName(endIf));
		predicate->codeGen(context, codes);
		//test %rax
		codes.push_back(Code(Code::AND, Reg::rax, Reg::rax));
		codes.push_back(Code(Code::JMZ, endIfLabel));
		sentence->codeGen(context, codes);
		codes.push_back(Code(Code::NOP));
		codes.back().addLabel(endIfLabel);
	}

	void NodeSIf::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSIf" << std::endl;
		predicate->dumpAST(cout, indent + 2);
		sentence->dumpAST(cout, indent + 2);
	}

	void NodeSIf::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSIf" << std::endl;
		predicate->dumpSem(cout, indent + 2);
		sentence->dumpSem(cout, indent + 2);
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

	void NodeSWhile::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSWhile" << std::endl;
		predicate->dumpSem(cout, indent + 2);
		sentence->dumpSem(cout, indent + 2);
	}

	void NodeSWhile::annotateType(std::map<std::string, int>& numOfSymbol,
								  std::map<Symbol, IdenDeco>& nameOfSymbol,
								  const FunctionMapNameOrdered& functionMap,
								  SemanticContext context, Errors& errs)
	{
		predicate->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		context.pwhile = this;
		//if will start a new scope even though there's no block
		std::map<Symbol, IdenDeco> currentNameOfSymbol = nameOfSymbol;
		sentence->annotateType(numOfSymbol, currentNameOfSymbol, functionMap, context, errs);
		Symbol pt = predicate->getType();
		if (!pt.same("int"))
			errs.push_back(Error("Semantic Analysis",
				getLine(),
				"Return type of the predicate in \"while\" shou be \"int\", not \"" + pt.getString() + "\"."));
	}

	void NodeSWhile::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		std::string startOfWhile = std::string("endOfIf");
		Label startOfWhileLabel(context.allocator->addName(startOfWhile));
		std::string endOfWhile = std::string("endOfIf");
		Label endOfWhileLabel(context.allocator->addName(endOfWhile));
		context.continueLabel = startOfWhileLabel;
		context.breakLabel = endOfWhileLabel;
		//oldSize is used to attach start label at first line of predicate
		int oldSize = codes.size();
		predicate->codeGen(context, codes);
		codes[oldSize].addLabel(startOfWhileLabel);
		//loop logic
		//test %rax
		codes.push_back(Code(Code::AND, Reg::rax, Reg::rax));
		codes.push_back(Code(Code::JMZ, endOfWhileLabel));
		sentence->codeGen(context, codes);
		codes.push_back(Code(Code::JMP, startOfWhileLabel));
		codes.push_back(Code(Code::NOP));
		codes.back().addLabel(endOfWhileLabel);
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

	void NodeSBlock::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSBlock" << std::endl;
		sentences->dumpSem(cout, indent + 2);
	}

	void NodeSBlock::annotateType(std::map<std::string, int>& numOfSymbol,
								  std::map<Symbol, IdenDeco>& nameOfSymbol,
								  const FunctionMapNameOrdered& functionMap,
								  SemanticContext context, Errors& errs)
	{
		//inside a block is a new scope
		//so have to set new nameOfSymbol context
		std::map<Symbol, IdenDeco> currentNameOfSymbol = nameOfSymbol;
		sentences->annotateType(numOfSymbol, currentNameOfSymbol, functionMap, context, errs);
	}

	void NodeSBlock::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		for (auto sentence : *sentences)
			sentence->codeGen(context, codes);
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

	void NodeSDecl::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSDecl (Type: " << type.getString()
			<< ", NameDeco: " << nameDeco.getString() << ")" << std::endl;
	}

	void NodeSDecl::annotateType(std::map<std::string, int>& numOfSymbol,
								 std::map<Symbol, IdenDeco>& nameOfSymbol,
								 const FunctionMapNameOrdered& functionMap,
								 SemanticContext context, Errors& errs)
	{
		//step 1: get name@type@id
		Symbol name = this->name.value;
		Symbol type = this->type.value;
		//decide whether type is valid
		if (context.types->find(type) == context.types->end())
			errs.push_back(Error("", getLine(),
				"Unknown type \"" + type.getString() + "\" of variable \"" + name.getString() + "\"."));
		else
		{
			//if type is valid...
			IdenDeco deco = IdenDeco(name, type, numOfSymbol);
			//step 2: load nameDeco into nameOfSymbol
			nameDeco = deco.nameDeco;
			nameOfSymbol[name] = deco;
		}

	}

	void NodeSentences::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSentences (Size: " << size() << ")" << std::endl;
		for (const auto& e : *this)
			e->dumpAST(cout, indent + 2);
	}

	void NodeSentences::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSentences (Size: " << size() << ")" << std::endl;
		for (const auto& e : *this)
			e->dumpSem(cout, indent + 2);
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
									std::map<Symbol, IdenDeco>& nameOfSymbol, 
									const FunctionMapNameOrdered& functionMap, 
									SemanticContext context, Errors& errs)
	{
		//be aware that all sentences in sentence are in one scope
		//so nameOfSymbol will be passed to lower nodes on AST tree
		for (auto sentence : *this)
			sentence->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
	}


	void NodeSentences::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		for (auto sentence : *this)
			sentence->codeGen(context, codes);
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

	void NodeSExpr::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSExpr" << std::endl;
		expr->dumpSem(cout, indent + 2);
	}

	void NodeSExpr::annotateType(std::map<std::string, int>& numOfSymbol,
									std::map<Symbol, IdenDeco>& nameOfSymbol, 
									const FunctionMapNameOrdered& functionMap, 
									SemanticContext context, Errors& errs)
	{
		expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
	}

	void NodeSExpr::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		expr->codeGen(context, codes);
	}

	NodeSReturn::NodeSReturn(int l) :
		NodeSentence(l, Node::NdSReturn), expr(NULL), pfunction(NULL)
	{
	}


	NodeSReturn::NodeSReturn(NodeExpr* e) :
		NodeSentence(e->getLine(), Node::NdSReturn), expr(e), pfunction(NULL)
	{
	}

	void NodeSReturn::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSReturn" << std::endl;
		if (expr != NULL)
			expr->dumpAST(cout, indent + 2);
	}

	void NodeSReturn::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSReturn (Return position: #" << pfunction->getLine() << ")" << std::endl;
		if (expr != NULL)
			expr->dumpSem(cout, indent + 2);
	}	

	void NodeSReturn::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		//check return type
		pfunction = context.pfunction;
		if (expr == NULL)
		{
			if (!(pfunction->returnType.value.same("void")))
			{
				errs.push_back(Error("", getLine(),
				std::string("Return type \"void\" does not match with definition \"" + pfunction->returnType.value.getString() + "\".")));
			}
			return;
		}
		else
		{
			expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
			Symbol ret = context.returnType;
			if (!(ret == expr->getType()))
			{
				errs.push_back(Error("", getLine(),
					std::string("Return type \"") + expr->getType().getString() +
					"\" does not match with definition \"" + ret.getString() + "\"."));
			}
		}
	}

	void NodeSReturn::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		expr->codeGen(context, codes);
		//return value are already store in %rax
		codes.push_back(Code(Code::JMP, context.returnLabel));
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

	void NodeSContinue::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSContinue (Return position: #" << pwhile->getLine() << ")" << std::endl;
	}

	void NodeSContinue::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		//make sure continue is inside a loop and set pwhile
		if (context.pwhile == NULL)
			errs.push_back(Error("", getLine(),
				std::string("\"continue\" should be used inside a loop.")));
		else pwhile = context.pwhile;
	}

	void NodeSContinue::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		codes.push_back(Code(Code::JMP, context.continueLabel));	
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

	void NodeSBreak::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeSBreak (Return position: #" << pwhile->getLine() << ")" << std::endl;
	}

	void NodeSBreak::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		//make sure continue is inside a loop and set pwhile
		if (context.pwhile == NULL)
			errs.push_back(Error("", getLine(),
				std::string("\"break\" should be used inside a loop.")));
		else pwhile = context.pwhile;
	}

	void NodeSBreak::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		codes.push_back(Code(Code::JMP, context.breakLabel));
	}
}

