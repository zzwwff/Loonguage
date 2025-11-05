#pragma once
#include "Node.h"
#include "NodeFunction.h"
namespace Loonguage {
	class NodeProgram:
		public Node
	{
	public:
		NodeFunctions* functions;
		NodeProgram();
		NodeProgram(NodeFunctions*);
		void dump(std::ostream&, int) const;
	};
}
