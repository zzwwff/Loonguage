#include "Error.h"
namespace Loonguage{
	Error::Error(std::string t, int l, std::string s):
		status(t), line(l), msg(s)
	{
	}

	Error::Error(std::string t, std::string s) :
		status(t), line(-1), msg(s)
	{
	}
	void Error::dump(std::ostream& cout) const
	{
		cout << "[" << status << "] ";
		if (line >= 0)
			cout << "An error occurred at line " << line << ": " << msg << std::endl;
		else cout << "An error occurred: " << msg << std::endl;
	}



	void Errors::dump(std::ostream& cout) const
	{
		for (const auto& e : *this)
			e.dump(cout);
	}

}

