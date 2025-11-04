#include "NodeFormal.h"


namespace Loonguage {
	NodeFormal::NodeFormal(NodeExpr* e) :
		Node(e->getLine(), Node::NdFormal), expr(e)
	{
	}

	NodeFormals::NodeFormals(NodeFormal* n) :
		Node(n->getLine(), Node::NdFormals)
	{
		push_back(n);
	}
}