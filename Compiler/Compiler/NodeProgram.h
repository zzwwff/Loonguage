#pragma once
#include "Node.h"
#include "NodeFunction.h"
namespace Loonguage {
	class NodeProgram:
		public Node
	{
		NodeFunctions* functions;
	public:
		NodeProgram();
		NodeProgram(NodeFunctions*);
		void dump(std::ostream&, int) const;
	};
}
