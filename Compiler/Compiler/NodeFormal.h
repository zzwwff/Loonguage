#pragma once
#include "Node.h"
#include "TokenIden.h"
#include <vector>
namespace Loonguage {
	class NodeFormal :
		public Node
	{
		TokenIden type;
		TokenIden name;
	public:
		NodeFormal(TokenIden, TokenIden);
		void dump(std::ostream&, int) const;
	};

	class NodeFormals :
		public std::vector<NodeFormal*>,
		public Node
	{
	public:
		void dump(std::ostream&, int) const;
		NodeFormals(NodeFormal*);
		NodeFormals(int);
	};
}
