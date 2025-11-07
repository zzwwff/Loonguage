#pragma once
#include "Node.h"
#include "TokenIden.h"
#include <vector>
namespace Loonguage {
	class NodeFormal :
		public Node
	{
	public:
		TokenIden type;
		TokenIden name;
		Symbol nameDeco;
		NodeFormal(TokenIden, TokenIden);
		void dumpSem(std::ostream&, int) const;
		void dumpAST(std::ostream&, int) const;
	};

	class NodeFormals :
		public std::vector<NodeFormal*>,
		public Node
	{
	public:
		void dumpSem(std::ostream&, int) const;
		void dumpAST(std::ostream&, int) const;

		NodeFormals(NodeFormal*);
		NodeFormals(int);
	};
}
