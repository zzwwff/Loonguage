#include "Compiler.h"

namespace Loonguage {
	Compiler::Compiler(std::istream& i, std::ostream& o1, std::ostream& o2, std::ostream& o3, std::ostream& o4):
		scanner(), 
		parser(scanner, idenTable, strTable, &program, errs),
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
			infoOut << "Lexical and syntax analysis are implemented successfully." << std::endl;
			program->dump(lexSynOut, 0);
			return true;
		}

	}

	//VecLess is used to compare signature of functions
	//It only compare whether the type of all parameters are all the same
	template <typename T>
	class VecLess {
	public:
		bool operator() (const T& v1, const T& v2) const
		{
			for (int i = 1; i < v1.size() && v2.size(); i++)
				if (v1[i] < v2[i])
					return true;
				else if (v1[i] > v2[i])
					return false;
			if (v1.size() < v2.size())
				return true;
			if (v1.size() > v2.size())
				return false;
		}
	};

	bool Compiler::semanticAnalysis(int debug = 0)
	{
		using Symbol = decltype(idenTable)::Symbol;
		//Phase 3: Semantic analysis
		//Multiple tasks will be executed in semantic analysis
		//Phase 3-1: Function Decoration
		NodeFunctions* functions = program->functions;
		for (const auto& function : *functions)
		{
			FunctionDeco funcDeco(function);
			if (functionDeco.find(funcDeco) != functionDeco.end())
			{
				errs.push_back(Error("Semantic Analysis", function->getLine(), ""));
			}
			functionDeco[funcDeco] = 1;
		}
		

		if (errs.size() == 0)
			semOut << "Semantic analysis are implemented successfully." << std::endl;
		else
		{
			semOut << "Compiling halted due to error(s) in semantic analysis." << std::endl;
			errs.dump(semOut);
		}
		//debug == 1: Output Debug
		semOut << "Function with decorated name:" << std::endl;
		for (auto func : functionDeco)
			semOut << func.first.nameDeco << std::endl;
		semOut << std::endl;
		return errs.size() == 0;
	}

	bool Compiler::parse()
	{
		infoOut << "Compiling begin..." << std::endl;
		//There are altogether 4 phases in compiling, all are integrated into function parse()
		//In parse(), the 4 phases will be executed one by one, and if error(s) occurred, will immediately terminate
		if (!lexicalAndSyntaxAnalysis())
			return false;
		if (!semanticAnalysis())
			return false;
	}


};

