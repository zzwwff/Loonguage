#include "NodeFunction.h"
namespace Loonguage {
	NodeFunction::NodeFunction(TokenIden rt, TokenIden n, std::shared_ptr<NodeFormals> a, std::shared_ptr<NodeSentence> s) :
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
		//note that pfunction is native pointer, because pfunction is not a path on AST tree
		context.pfunction = this;
		context.returnType = returnType.value;
		//call annotateType inside the function body
		sentence->annotateType(numOfSymbol, currentNameOfSymbol, functionMap, context, errs);
	}

	void NodeFunction::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		std::string callStr = std::string("call@") + nameDeco.getString();
		Label callLabel(context.allocator->addName(callStr));
		std::string returnStr = std::string("return@") + nameDeco.getString();
		Label returnLabel(context.allocator->addName(returnStr));

		//offset of formals from %rfp
		for (int i = 0; i < formals->size(); i++)
			context.delta[(*formals)[i]->nameDeco] = i;
		//offset of locals
		for (int i = 0; i < locals.size(); i++)
			context.delta[locals[i]] = i + formals->size();

		//update rsp
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, -context.width * locals.size()));

		sentence->codeGen(context, codes);

		//pop back all parameters
		//attach returnLabel to the first instruction, make sure that %rax is set at 'return'
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, context.width * locals.size()));
		codes.back().addLabel(returnLabel);
		//return
		codes.push_back(Code(Code::JR, Reg::ret));
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

	NodeFunctions::NodeFunctions(std::shared_ptr<NodeFunction> f):
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

	void NodeFunctions::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		for (auto function : *this)
			function->codeGen(context, codes);
	}

	NodeNativeFunction::NodeNativeFunction(TokenIden r, TokenIden n, std::shared_ptr<NodeFormals> f) :
		NodeFunction(r, n, f, nullptr)
	{
	}

	void NodeNativeFunction::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeNativeFunction (Return Type: " << returnType.getString()
			<< ", Name: " << name.getString() << ")" << std::endl;
		formals->dumpAST(cout, indent + 2);
	}

	void NodeNativeFunction::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeNativeFunction (Return Type: " << returnType.getString()
			<< ", NameDeco: " << nameDeco.getString() << ")" << std::endl;
		formals->dumpSem(cout, indent + 2);
	}

	void NodeNativeFunction::annotateType(std::map<std::string, int>& numOfSymbol,
										  std::map<Symbol, IdenDeco>& nameOfSymbol,
										  const FunctionMapNameOrdered& functionMap,
										  SemanticContext context, Errors& errs)
	{
		//copy from NodeFunction::annotateType
		//some line will be annotated

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
		//note that pfunction is native pointer, because pfunction is not a path on AST tree
		//context.pfunction = this;
		context.returnType = returnType.value;
		//call annotateType inside the function body
		//sentence->annotateType(numOfSymbol, currentNameOfSymbol, functionMap, context, errs);
	}

	void NodeNativeFunction::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		std::string callStr = std::string("call@") + nameDeco.getString();
		Label callLabel(context.allocator->addName(callStr));
		std::string returnStr = std::string("return@") + nameDeco.getString();
		Label returnLabel(context.allocator->addName(returnStr));

		//offset of formals from %rfp
		for (int i = 0; i < formals->size(); i++)
			context.delta[(*formals)[i]->nameDeco] = i;
		//offset of locals
		for (int i = 0; i < locals.size(); i++)
			context.delta[locals[i]] = i + formals->size();

		//update rsp
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, -context.width * locals.size()));

		builtInCodeGen(context, codes);

		//pop back all parameters
		//attach returnLabel to the first instruction, make sure that %rax is set at 'return'
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, context.width * locals.size()));
		codes.back().addLabel(returnLabel);
		//return
		codes.push_back(Code(Code::JR, Reg::ret));
	}

    void NodeNativeFunction::builtInCodeGen(CodeGenContext& context, std::vector<Code>& codes)

    {
        if (nameDeco.getString() == "out@int")
        {
            codes.push_back(Code(Code::MOVRM, Reg::rax, Address(Reg::rfp, 0)));
            codes.push_back(Code(Code::OUT, Reg::rax));
        }
        if (nameDeco.getString() == "getChar@string@int")
        {
            codes.push_back(Code(Code::MOVRM, Reg::rax, Address(Reg::rfp, 0)));
            codes.push_back(Code(Code::MOVRM, Reg::rtm, Address(Reg::rfp, -context.width)));
            codes.push_back(Code(Code::SUB, Reg::rax, Reg::rtm));
            codes.push_back(Code(Code::MOVRMB, Reg::rax, Address(Reg::rax, -1)));
        }
        if (nameDeco.getString() == "getSize@string")
        {
            codes.push_back(Code(Code::MOVRM, Reg::rax, Address(Reg::rfp, 0)));
            codes.push_back(Code(Code::MOVRMB, Reg::rax, Address(Reg::rax, 0)));
        }
    }
}
