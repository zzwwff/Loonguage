#pragma once
#include <vector>
#include "NodeExpr.h"
#include "Node.h"
namespace Loonguage {
	class NodeExpr;

	class NodeActual :
		public Node
	{
		NodeExpr* expr;
	public:
		NodeActual(NodeExpr*);
		void dump(std::ostream&, int) const;
	};

	class NodeActuals :
		public std::vector<NodeActual*>,
		public Node
	{
	public:
		NodeActuals(NodeActual*);
		NodeActuals(int);
		void dump(std::ostream&, int) const;
	};
}

