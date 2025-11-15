#include "Compiler.h"
#include "IdenDeco.h"
#include "location.hh"
//#include "lex.Loon_.cc"
namespace Loonguage {

	void Compiler::registerDefaultTypes()
	{
		types[idenTable.addSymbol("int")] = 1;
		types[idenTable.addSymbol("string")] = 1;
		//symbol 'void' will be used
		//but void is not a kind of type
		idenTable.addSymbol("void");
	}


	void Compiler::functionDecoration()
	{
		auto functions = program->functions;
		for (auto& function : *functions)
		{
			bool valid = true;
			FunctionDeco funcDeco(function.get());
			//check parameters type
			for (const auto& t : funcDeco.paramType)
			{
				if (types.find(t) == types.end())
				{
					errs.push_back(Error("Semantic Analysis", function->getLine(), "Unknown parameter type \"" + t.getString() + "\" in function \"" + funcDeco.name.getString() + "\"."));
					valid = false;
				}
			}
			//check names are distinct
			std::map<Symbol, int> names;
			for (const auto& t : funcDeco.paramName)
			{
				if (names.find(t) != names.end())
				{
					errs.push_back(Error("Semantic Analysis", function->getLine(), "Redefined parameter name \"" + t.getString() + "\" in function \"" + funcDeco.name.getString() + "\"."));
					valid = false;
				}
				else names[t] = 1;
			}
			//check return type
			if (types.find(funcDeco.returnType) == types.end())
			{
				if (!(funcDeco.returnType == idenTable["void"]))
				{
					errs.push_back(Error("Semantic Analysis", function->getLine(), "Unknown return type \"" + funcDeco.returnType.getString() + "\" in function \"" + funcDeco.name.getString() + "\"."));
					valid = false;
				}

			}
			//check redefined functions(same function with same parameter type)
			if (functionDeco.find(funcDeco) != functionDeco.end())
			{
				errs.push_back(Error("Semantic Analysis", function->getLine(), "Function \"" + funcDeco.name.getString() + "\" redefined."));
			}
			if (valid)
			{
				functionDeco[funcDeco] = 1;
				function->nameDeco = funcDeco.nameDeco;
			}
		}
		//sort all the decorated name by function name
		//for overload resolution
		for (auto iter = functionDeco.begin(); iter != functionDeco.end(); iter++)
			functionDecoNameOrdered[iter->first.name].push_back(iter);
	}

	Compiler::Compiler(std::istream& i, std::ostream& o1, std::ostream& o2, std::ostream& o3, std::ostream& o4):
		scanner(),
		loc(LoonScanner::location()),
		parser(scanner, loc, idenTable, strTable, program, errs),
		program(NULL),
		cin(i), infoOut(o1), lexSynOut(o2), semOut(o3), genOut(o4)
	{
		//set cin and cout
		scanner.switch_streams(cin, lexSynOut);
	}



	bool Compiler::lexicalAndSyntaxAnalysis()
	{
		//Phase 1: Lexical analysis
		//Phase 2: Syntax analysis
		//2 phases are merged and are implemented at the same time
		parser.parse();
		if (errs.size())
		{
			infoOut << "Compiling halted due to error(s) in lexical and syntax analysis." << std::endl;
			errs.dump(lexSynOut);
			return false;
		}
		else
		{
			infoOut << "Lexical and syntax analysis is implemented successfully." << std::endl;
			program->dumpAST(lexSynOut, 0);
			return true;
		}

	}


	bool Compiler::semanticAnalysis(int debug = 0)
	{
		//Phase 3: Semantic analysis
		//Multiple tasks will be executed in semantic analysis
		//Phase 3-1: Collect all types
		registerDefaultTypes();

		//Phase 3-2: Function Decoration
		//check that types of formals are valid
		//check that return type is void or valid type
		//check that names of formals are distinct
		functionDecoration();

		//Phase 3-3: type check
		//set wrong type
		idenTable.wrongType = idenTable.addSymbol("@error");
		//traverse the AST upside down and annotate type downside up
		//show how many times has symbol@type be used
		std::map<std::string, int> numOfSymbol;
		//show what is the current implication of symbol
		std::map<Symbol, IdenDeco> decoOfSymbol;
		//record nearest function and while(used for continue/return/break)
		SemanticContext context = { Symbol(), NULL, NULL, idenTable, types };
		//annotate from root
		program->annotateType(numOfSymbol, decoOfSymbol, functionDecoNameOrdered, context, errs);

		//semantic analysis completed
		if (errs.size() == 0)
		{
			infoOut << "Semantic analysis is implemented successfully." << std::endl;
			//watch out that dumpSem is available only when no error occur
			program->dumpSem(semOut, 0);
		}
		else
		{
			infoOut << "Compiling halted due to error(s) in semantic analysis." << std::endl;
			for (auto& err : errs)
				if (err.status.size() == 0)
					err.status = "Semantic Analysis";
			errs.dump(semOut);
		}
		//debug == 1: Output Debug
		semOut << "Function with decorated name:" << std::endl;
		for (auto func : functionDeco)
			semOut << func.first.nameDeco.getString() << std::endl;
		semOut << std::endl;
		return errs.size() == 0;
	}

	//generate ASM code
	bool Compiler::codeGeneration()
	{
		std::shared_ptr<LabelAllocator> alloc =  std::make_shared<LabelAllocator>();
		CodeGenContext context;
        context.width = 8;
		context.allocator = alloc;
        codes.push_back(Code(Code::CALL, Label("call@main")));
        codes.push_back(Code(Code::HLT));
        program->codeGen(context, codes);
		//no bug will be reported in code generation
		for (auto code : codes)
			code.dump(genOut);
		infoOut << "Code generation is implemented successfully." << std::endl;
		return true;
	}

	bool Compiler::parse()
	{
		infoOut << "Compiling begin..." << std::endl;
		//There are altogether 4 phases in compiling, all are integrated into function Compiler::parse()
		//In parse(), the 4 phases will be executed one by one, and if error(s) occurred, will immediately terminate
		if (!lexicalAndSyntaxAnalysis())
            return runable = false;
		if (!semanticAnalysis())
            return runable = false;
		if (!codeGeneration())
            return runable = false;
        return runable = true;
	}


};

