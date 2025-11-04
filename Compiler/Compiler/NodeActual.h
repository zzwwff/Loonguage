#pragma once
#include "Node.h"
#include "TokenIden.h"
#include <vector>
namespace Loonguage {
	class NodeActual :
		public Node
	{
		TokenIden type;
		TokenIden name;
	public:
		NodeActual(TokenIden, TokenIden);
		void dump(std::ostream&, int) const;
	};

	class NodeActuals :
		public std::vector<NodeActual*>,
		public Node
	{
	public:
		void dump(std::ostream&, int) const;
		NodeActuals(NodeActual*);
	};
}
