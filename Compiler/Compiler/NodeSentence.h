#pragma once
#include "Node.h"
#include "TokenIden.h"
#include "NodeExpr.h"
#include <vector>
namespace Loonguage {
	class NodeSentence :
		public Node
	{
	public:
		NodeSentence(int, Node::NodeType);
	};

	class NodeSentences :
		public std::vector<NodeSentence*>,
		public Node
	{
	public:
		void dump(std::ostream&, int) const;
		NodeSentences(NodeSentence*);
	};

	class NodeSExpr :
		public NodeSentence
	{
		NodeExpr* expr;
	public:
		NodeSExpr(NodeExpr*);
		void dump(std::ostream&, int) const;
	};

	class NodeSIf :
		public NodeSentence
	{
		NodeExpr* predicate;
		NodeSentence* sentence;
	public:
		NodeSIf(NodeExpr*, NodeSentence*);
		void dump(std::ostream&, int) const;
	};

	class NodeSWhile :
		public NodeSentence
	{
		NodeExpr* predicate;
		NodeSentence* sentence;
	public:
		NodeSWhile(NodeExpr*, NodeSentence*);
		void dump(std::ostream&, int) const;
	};

	class NodeSBlock :
		public NodeSentence
	{
		NodeSentences* sentences;
	public:
		NodeSBlock(NodeSentences*);
		void dump(std::ostream&, int) const;
	};

	class NodeSDecl :
		public NodeSentence
	{
		TokenIden type;
		TokenIden name;
	public:
		NodeSDecl(TokenIden, TokenIden);
		void dump(std::ostream&, int) const;
	};
}
