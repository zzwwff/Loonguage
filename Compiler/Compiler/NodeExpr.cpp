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

	NodeEBracket::NodeEBracket(NodeExpr* e):
		NodeExpr(e->getLine(), Node::NdEBracket), expr(e)
	{
	}

	void NodeEBracket::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << std::endl;
		expr->dumpAST(cout, indent + 2);
	}

	void NodeEBracket::annotateType(std::map<std::string, int>& numOfSymbol,
		std::map<Symbol, IdenDeco>& nameOfSymbol,
		const FunctionMapNameOrdered& functionMap,
		SemanticContext context, Errors& errs)
	{
		expr->annotateType(numOfSymbol, nameOfSymbol, functionMap, context, errs);
		type = expr->type;
	}

	NodeEDispatch::NodeEDispatch(TokenIden i, NodeActuals* a):
		NodeExpr(i.line, Node::NdEDispatch), iden(i), actuals(a)
	{
	}

	void NodeEDispatch::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEDispatch (Iden:" << iden.getString() << ")" << std::endl;
		actuals->dumpAST(cout, indent + 2);
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

	NodeECalc::NodeECalc(NodeExpr* e1, char c, NodeExpr* e2):
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

	NodeEEqua::NodeEEqua(NodeExpr* e1, NodeExpr* e2):
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

	NodeELess::NodeELess(NodeExpr* e1, NodeExpr* e2) :
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

	NodeERev::NodeERev(NodeExpr* e):
		NodeExpr(e->getLine(), Node::NdERev), expr(e)
	{
	}
	void NodeERev::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeERev" << std::endl;
		expr->dumpAST(cout, indent + 2);
	}

	NodeEAssign::NodeEAssign(TokenIden i, NodeExpr* e):
		NodeExpr(i.line, Node::NdEAssign),  expr(e), iden(i)
	{
	}

	void NodeEAssign::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEAssign (Iden:" << iden.getString() << ")" << std::endl;
		expr->dumpAST(cout, indent + 2);
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

	NodeEStr::NodeEStr(TokenString s):
		NodeExpr(s.line, Node::NdEStr), str(s)
	{
	}
	void NodeEStr::dumpAST(std::ostream& cout, int indent) const
	{
		Node::indent(cout, indent);
		cout << "#" << line << ": NodeEStr (Value:\"" << str.getValue() << "\")" << std::endl;
	}
}