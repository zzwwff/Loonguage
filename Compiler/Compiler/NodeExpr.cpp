#include "NodeExpr.h"
#include "NodeFunction.h"
namespace Loonguage {
	Node::Symbol NodeExpr::getType() const
	{
		return type;
	}
	NodeExpr::NodeExpr(int l, Node::NodeType t) :
		Node(l, t)
	{

	}

	void NodeExpr::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{

	}

	NodeEIden::NodeEIden(TokenIden i):
		NodeExpr(i.line, Node::NdEIden), iden(i)
	{
	}

	void NodeEIden::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEIden (Name:" << iden.getString()
			<< ")" << std::endl;
	}

	void NodeEIden::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEIden (idenDeco:" << idenDeco.getString()
			<< ", Type: " << type.getString() << ")" << std::endl;
	}

	void NodeEIden::annotateType(std::map<std::string, int>& numOfSymbol,
								 std::map<Symbol, IdenDeco>& nameOfSymbol,
								 const FunctionMapNameOrdered& functionMap,
								 SemanticContext context, Errors& errs)
	{
		if (nameOfSymbol.find(iden.value) == nameOfSymbol.end())
		{
			errs.push_back(Error("", getLine(),
				std::string("Unknown identifier \"" + iden.value.getString() + "\".")));
			idenDeco = type = iden.value.getWrongType();
		}
		else
		{
			idenDeco = nameOfSymbol[iden.value].nameDeco;
			type = nameOfSymbol[iden.value].type;
		}
	}

	void NodeEIden::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		codes.push_back(Code(Code::LW, Reg::rfp, Reg::rax, -context.width * context.delta[idenDeco]));
	}

	NodeEIdenArray::NodeEIdenArray(TokenIden i, std::shared_ptr<NodeExpr> o) :
		NodeExpr(i.line, Node::NdEIdenArray), iden(i), offset(o)
	{
	}

	void NodeEIdenArray::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEIdenArray (Name:" << iden.getString()
			<< ")" << std::endl;
		offset->dumpAST(cout, indent + 2);
	}

	void NodeEIdenArray::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEIdenArray (idenDeco:" << idenDeco.getString()
			<< ")" << std::endl;
		offset->dumpSem(cout, indent);
	}

	void NodeEIdenArray::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		offset->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		if (!offset->type.same("int"))
		{
			errs.push_back(Error("", getLine(),
				std::string("Type of index must be \"int\".")));
			idenDeco = type = iden.value.getWrongType();
		}
		else if (nameOfSymbol.find(iden.value) == nameOfSymbol.end())
		{
			errs.push_back(Error("", getLine(),
				std::string("Unknown identifier \"" + iden.value.getString() + "\".")));
			idenDeco = type = iden.value.getWrongType();
		}
		else if (nameOfSymbol.find(iden.value)->second.type.same("ints"))
		{
			idenDeco = nameOfSymbol[iden.value].nameDeco;
            type = idenDeco.getPointer()->operator[]("int");
		}
		else 
			errs.push_back(Error("", getLine(),
				std::string("Operator \"[]\" can only be used on array.")));
	}

	void NodeEIdenArray::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		//get offset in $rax
		offset->codeGen(context, codes);
		//get base in $rtm
		codes.push_back(Code(Code::ADDI, Reg::rfp, Reg::rtm, -context.width * context.delta[idenDeco]));
		//target is $rtm - 4 * $rax, saved in $rax
		codes.push_back(Code(Code::ORI, Reg::rze, Reg::rbx, 4));
		codes.push_back(Code(Code::MUL, Reg::rax, Reg::rbx, Reg::rax));
		codes.push_back(Code(Code::SUB, Reg::rtm, Reg::rax, Reg::rax));
		codes.push_back(Code(Code::LW, Reg::rax, Reg::rax, 0));
	}


	NodeEBracket::NodeEBracket(std::shared_ptr<NodeExpr> e):
		NodeExpr(e->getLine(), Node::NdEBracket), expr(e)
	{
	}

	void NodeEBracket::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEBracket" << std::endl;
		expr->dumpAST(cout, indent + 2);
	}

	void NodeEBracket::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEBracket" << "(Type: " << type.getString() << ")" << std::endl;
		expr->dumpSem(cout, indent + 2);
	}

	void NodeEBracket::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		type = expr->type;
	}

	void NodeEBracket::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		expr->codeGen(context, codes);
	}

	NodeEDispatch::NodeEDispatch(TokenIden i, std::shared_ptr<NodeActuals> a):
		NodeExpr(i.line, Node::NdEDispatch), iden(i), actuals(a)
	{
	}

	void NodeEDispatch::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEDispatch (Iden:" << iden.getString() << ")" << std::endl;
		actuals->dumpAST(cout, indent + 2);
	}

	void NodeEDispatch::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEDispatch (idenDeco:" << idenDeco.getString() << ", Type: " << type.getString() << ")" << std::endl;
		actuals->dumpSem(cout, indent + 2);
	}

	void NodeEDispatch::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		//name of function not found
		if (functionMap.find(iden.value) == functionMap.end())
		{
			errs.push_back(Error("", getLine(), "Unknown function \"" + iden.value.getString() + "\"."));
			type = iden.value.getWrongType();
			return;
		}
		for (auto actual : *actuals)
			actual->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		//overloading resolution
		for (const auto& fuc : functionMap.at(iden.value))
		{
			const auto& types = fuc->first.paramType;
			bool signal = (types.size() == actuals->size());
			//check all types are the same
			for (int i = 0; i < types.size() && signal; i++)
			{
				if (!(types[i] == ((*actuals)[i])->type))
					signal = false;
			}
			//resolution done, update type and idenDeco
			if (signal)
			{
				type = fuc->first.returnType;
				idenDeco = fuc->first.nameDeco;
				return;
			}
		}
		//no match for function
		errs.push_back(Error("", getLine(), "No match for function \"" + iden.value.getString() + "\"."));
		type = iden.value.getWrongType();
		return;
	}

	void NodeEDispatch::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{

		std::string callLabel = std::string("call@") + idenDeco.getString();

		//load all parameters
		for (int i = 0; i < actuals->size(); i++)
		{
			(*actuals)[i]->codeGen(context, codes);
			codes.push_back(Code(Code::SW, Reg::rsp, Reg::rax, -context.width * (i + 2)));
		}

		//save %ret, save %rfp
		codes.push_back(Code(Code::SW, Reg::rsp, Reg::ret, 0));
		codes.push_back(Code(Code::SW, Reg::rsp, Reg::rfp, -context.width));

		//set %rfp and %rsp
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rfp, -2 * context.width));
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, -(actuals->size() + 2) * context.width));
		codes.push_back(Code(Code::JAL, Label(callLabel)));
		//reset %rfp and %rsp and %ret
		codes.push_back(Code(Code::ADDI, Reg::rfp, Reg::rsp, 2 * context.width));
		codes.push_back(Code(Code::LW, Reg::rsp, Reg::rfp, -context.width));
		codes.push_back(Code(Code::LW, Reg::rsp, Reg::ret, 0));
	}

	NodeECalc::NodeECalc(std::shared_ptr<NodeExpr> e1, char c, std::shared_ptr<NodeExpr> e2):
		NodeExpr(e1->getLine(), Node::NdECalc), expr1(e1), op(c), expr2(e2)
	{
	}

	void NodeECalc::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeECalc (Op:" << op << ")" << std::endl;
		expr1->dumpAST(cout, indent + 2);
		expr2->dumpAST(cout, indent + 2);
	}

	void NodeECalc::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeECalc (Op:" << op << ", Type: " << type.getString() << ")" << std::endl;
		expr1->dumpSem(cout, indent + 2);
		expr2->dumpSem(cout, indent + 2);
	}

	void NodeECalc::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		expr1->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		expr2->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		if ((!expr1->type.same("int")) || (!expr2->type.same("int")))
		{
			errs.push_back(Error("", getLine(), std::string("At operator \"") + op + "\": Only type \"int\" can be calculated."));
			type = expr1->getType().getWrongType();
		}
		else type = (*(expr1->getType().getPointer()))["int"];
	}

	void NodeECalc::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		expr2->codeGen(context, codes);
        codes.push_back(Code(Code::SW, Reg::rsp, Reg::rax, 0));
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, -context.width));
		expr1->codeGen(context, codes);
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, context.width));
		codes.push_back(Code(Code::LW, Reg::rsp, Reg::rtm, 0));
		Code::CodeType type;
		if (op == '+') type = Code::ADD;
		else if (op == '-') type = Code::SUB;
		else if (op == '*') type = Code::MUL;
        else if (op == '/' || op == '%') type = Code::DIV;
		else if (op == '&') type = Code::AND;
		else if (op == '|') type = Code::OR;
		else if (op == '^') type = Code::XOR;
        codes.push_back(Code(type, Reg::rax, Reg::rtm, Reg::rax));
		if (op == '/')
			codes.push_back(Code(Code::MFLO, Reg::rax));
		else if (op == '%')
			codes.push_back(Code(Code::MFHI, Reg::rax));
    }

	NodeEEqua::NodeEEqua(std::shared_ptr<NodeExpr> e1, std::shared_ptr<NodeExpr> e2):
		NodeExpr(e1->getLine(), Node::NdEEqua), expr1(e1), expr2(e2)
	{
	}

	void NodeEEqua::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEEqua" << std::endl;
		expr1->dumpAST(cout, indent + 2);
		expr2->dumpAST(cout, indent + 2);
	}

	void NodeEEqua::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEEqua (Type: " << type.getString() << ")" << std::endl;
		expr1->dumpSem(cout, indent + 2);
		expr2->dumpSem(cout, indent + 2);
	}

	void NodeEEqua::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		expr1->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		expr2->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		if ((!expr1->type.same("int")) || (!expr2->type.same("int")))
		{
			errs.push_back(Error("", getLine(), std::string("At operator \"==\": Only type \"int\" can be compared.")));
			type = expr1->getType().getWrongType();
		}
		else type = (*(expr1->getType().getPointer()))["int"];
	}

	void NodeEEqua::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		expr2->codeGen(context, codes);
		codes.push_back(Code(Code::SW, Reg::rsp, Reg::rax, 0));
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, -context.width));
		expr1->codeGen(context, codes);
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, context.width));
		codes.push_back(Code(Code::LW, Reg::rsp, Reg::rtm, 0));
		//$rbx = $rax - $rtm = expr1 - expr2
		codes.push_back(Code(Code::SUB, Reg::rax, Reg::rtm, Reg::rbx));
		//make $rax = 0
		codes.push_back(Code(Code::ORI, Reg::rze, Reg::rax, 0));
		//make $rcx = 1
		codes.push_back(Code(Code::ORI, Reg::rze, Reg::rcx, 1));
		//if ($rbx == 0) which means expr1 == expr2 then set $rax = 1
		codes.push_back(Code(Code::MOVZ, Reg::rcx, Reg::rbx, Reg::rax));
	}

	NodeELess::NodeELess(std::shared_ptr<NodeExpr> e1, std::shared_ptr<NodeExpr> e2) :
		NodeExpr(e1->getLine(), Node::NdEEqua), expr1(e1), expr2(e2)
	{
	}

	void NodeELess::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeELess" << std::endl;
		expr1->dumpAST(cout, indent + 2);
		expr2->dumpAST(cout, indent + 2);
	}

	void NodeELess::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeELess (Type: " << type.getString() << ")" << std::endl;
		expr1->dumpSem(cout, indent + 2);
		expr2->dumpSem(cout, indent + 2);
	}

	void NodeELess::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		expr1->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		expr2->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		if ((!expr1->type.same("int")) || (!expr2->type.same("int")))
		{
			errs.push_back(Error("", getLine(), std::string("At operator \"<\": Only type \"int\" can be compared.")));
			type = expr1->getType().getWrongType();
		}
		else type = (*(expr1->getType().getPointer()))["int"];
	}


	void NodeELess::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		expr2->codeGen(context, codes);
		codes.push_back(Code(Code::SW, Reg::rsp, Reg::rax, 0));
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, -context.width));
		expr1->codeGen(context, codes);
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, context.width));
		codes.push_back(Code(Code::LW, Reg::rsp, Reg::rtm, 0));
		codes.push_back(Code(Code::SLT, Reg::rax, Reg::rtm, Reg::rax));
	}

	NodeERev::NodeERev(std::shared_ptr<NodeExpr> e):
		NodeExpr(e->getLine(), Node::NdERev), expr(e)
	{
	}
	void NodeERev::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeERev" << std::endl;
		expr->dumpAST(cout, indent + 2);
	}

	void NodeERev::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeERev (Type: " << type.getString() << ")" << std::endl;
		expr->dumpSem(cout, indent + 2);
	}

	void NodeERev::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		if (!expr->type.same("int"))
		{
			errs.push_back(Error("", getLine(), std::string("At operator \"~\": Only type \"int\" can be computed.")));
			type = expr->getType().getWrongType();
		}
		else type = expr->getType();
	}

	void NodeERev::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		expr->codeGen(context, codes);
		codes.push_back(Code(Code::NOT, Reg::rax, Reg::rax));
	}

	NodeEAssign::NodeEAssign(TokenIden i, std::shared_ptr<NodeExpr> e):
		NodeExpr(i.line, Node::NdEAssign),  expr(e), iden(i)
	{
	}

	void NodeEAssign::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEAssign (Iden:" << iden.getString() << ")" << std::endl;
		expr->dumpAST(cout, indent + 2);
	}

	void NodeEAssign::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEAssign (IdenDeco: " << idenDeco.getString() << ", Type: " << type.getString() << ")" << std::endl;
		expr->dumpSem(cout, indent + 2);
	}

	void NodeEAssign::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		if (nameOfSymbol.find(iden.value) == nameOfSymbol.end())
		{
			errs.push_back(Error("", getLine(), std::string("Unknown identifier \"") + iden.value.getString() + "\"."));
            type = iden.value.getWrongType();
			return;
		}
		Symbol idenType = nameOfSymbol[iden.value].type;
		idenDeco = nameOfSymbol[iden.value].nameDeco;
		expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		if (!(expr->type == idenType) && !(expr->type == expr->type.getWrongType()))
		{
			errs.push_back(Error("", getLine(), std::string("Types of value and object do not match.")));
			type = expr->getType().getWrongType();
		}
		else type = expr->getType();
	}

	void NodeEAssign::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		expr->codeGen(context, codes);
		codes.push_back(Code(Code::SW, Reg::rfp, Reg::rax, -context.width * context.delta[idenDeco]));
	}

	NodeEAssignArray::NodeEAssignArray(TokenIden i, std::shared_ptr<NodeExpr> o, std::shared_ptr<NodeExpr> e):
		NodeExpr(i.line, Node::NdEAssignArray), iden(i), offset(o), expr(e)
	{
	}

	void NodeEAssignArray::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEAssignArray (Iden: " << iden.getString()
			 << ")" << std::endl;
		expr->dumpAST(cout, indent + 2);
		offset->dumpAST(cout, indent + 2);
	}

	void NodeEAssignArray::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEAssignArray (IdenDeco: " << idenDeco.getString() << ", Type: " << type.getString()
			 << ")" << std::endl;
		expr->dumpSem(cout, indent + 2);
		offset->dumpSem(cout, indent + 2);
	}

	void NodeEAssignArray::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		offset->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		if (!offset->type.same("int"))
		{
			errs.push_back(Error("", getLine(),
				std::string("Type of index must be \"int\".")));
			idenDeco = type = iden.value.getWrongType();
			return;
		}
		else if (nameOfSymbol.find(iden.value) == nameOfSymbol.end())
		{
			errs.push_back(Error("", getLine(), std::string("Unknown identifier \"") + iden.value.getString() + "\"."));
			type = iden.value.getWrongType();
			return;
		}
		Symbol idenType = nameOfSymbol[iden.value].type;
		idenDeco = nameOfSymbol[iden.value].nameDeco;
		expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		if (!expr->type.same("int"))
		{
			errs.push_back(Error("", getLine(), std::string("Types of value and object do not match.")));
			type = expr->getType().getWrongType();
		}
		else if (nameOfSymbol.find(iden.value)->second.type.same("ints"))
		{
			type = expr->getType();
		}
		else
			errs.push_back(Error("", getLine(),
				std::string("Operator \"[]\" can only be used on array.")));
	}

	void NodeEAssignArray::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		//value in stack
		expr->codeGen(context, codes);
		codes.push_back(Code(Code::SW, Reg::rsp, Reg::rax, 0));
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, -context.width));

		//get offset in $rcx
		offset->codeGen(context, codes);
		codes.push_back(Code(Code::MOVZ, Reg::rax, Reg::rze, Reg::rcx));
		//get base in $rtm
		codes.push_back(Code(Code::ADDI, Reg::rfp, Reg::rtm, -context.width * context.delta[idenDeco]));
		//target is $rtm - 4 * $rax, saved in $rbx
		codes.push_back(Code(Code::ORI, Reg::rze, Reg::rbx, 4));
		codes.push_back(Code(Code::MUL, Reg::rax, Reg::rbx, Reg::rax));
		codes.push_back(Code(Code::SUB, Reg::rtm, Reg::rax, Reg::rbx));
		//get value from stack into $rax
		codes.push_back(Code(Code::ADDI, Reg::rsp, Reg::rsp, context.width));
		codes.push_back(Code(Code::LW, Reg::rsp, Reg::rax, 0));
		
		codes.push_back(Code(Code::SW, Reg::rbx, Reg::rax, 0));
	}


	NodeEInt::NodeEInt(TokenInt i):
		NodeExpr(i.line, Node::NdEInt), int_(i)
	{
	}

	void NodeEInt::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEInt (Value:" << int_.getValue() << ")" << std::endl;
	}

	void NodeEInt::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEInt (Value:" << int_.getValue() << ", Type: " << type.getString() << ")" << std::endl;
	}

	void NodeEInt::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		type = context.idenTable["int"];
	}

	void NodeEInt::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		codes.push_back(Code(Code::ORI, Reg::rze, Reg::rax, int_.getValue()));
	}

	NodeEStr::NodeEStr(TokenString s):
		NodeExpr(s.line, Node::NdEStr), str(s)
	{
	}
	void NodeEStr::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEStr (Value:\"" << str.getValue() << "\")" << std::endl;
	}

	void NodeEStr::dumpSem(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEStr (Value:\"" << str.getValue() << ", Type: " << type.getString() << ")" << std::endl;
	}

	void NodeEStr::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		type = context.idenTable["string"];
	}

	void NodeEStr::codeGen(CodeGenContext& context, std::vector<Code>& codes)
	{
		codes.push_back(Code(Code::ORI, Reg::rze, Reg::rax, context.strPosition[str.value]));
	}

}
