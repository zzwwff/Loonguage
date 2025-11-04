#pragma once
#include <vector>
#include "NodeExpr.h"
#include "Node.h"
namespace Loonguage {
	class NodeFormal :
		public Node
	{
		NodeExpr* expr;
	public:
		NodeFormal(NodeExpr*);
	};

	class NodeFormals :
		public std::vector<NodeFormal*>,
		public Node
	{
		NodeFormals(NodeFormal*);
	};
}

