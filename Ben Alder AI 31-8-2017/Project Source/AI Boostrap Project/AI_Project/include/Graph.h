#pragma once

#include <vector>

template<typename TNodeData, typename TEdgeData>
class Graph
{
public:

	Graph()	{}

	virtual ~Graph()
	{
		for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
		{
			delete (*iter);
		}

		m_nodes.clear();
	}

	struct Edge;
	struct Node;

	struct Node
	{
		TNodeData			data;
		std::vector<Edge>	edges;
	};
	
	struct Edge
	{
		Node		*to;
		TEdgeData	 data;
	};
	
	// TODO: add methdos for adding and removing nodes
	
	Node* AddNode(const TNodeData &data)
	{
		Node *node = new Node();
		node->data = data;

		m_nodes.push_back(node);
		return node;
	}

	void AddEdge(int NodeAIndex, int NodeBIndex, bool bidirectiona, const TEdgeData &data)
	{
		Node *nodeA = GetNodeByID(NodeAIndex);
		Node *nodeB = GetNodeByID(NodeBIndex);

		AddEdge(nodeA, nodeB, bidirectional, data);
	}

	void AddEdge(Node *nodeA, Node *nodeB, bool isBiDirectional, const TEdgeData &data)
	{
		Edge edge;
		edge.to		= nodeB;
		edge.data	= data;

		nodeA->edges.push_back(edge);

		if (isBiDirectional)
		{
			Edge edge2;
			edge2.to	= nodeA;
			edge2.data	= data;
			nodeB->edges.push_back(edge2);
		}
	}
	
	// returns the node at the location in the m_nodes
	Node *GetNodeById(int nodeId)
	{
		return m_nodes[nodeId];
	}
	
	const std::vector<Node *>& GetNodes() const
	{
		return m_nodes;
	}

	//bool IsCyclic(); // OPTIONAL: returns true if cyclic, false if acylic
	//bool IsConnected(); // OPTIONAL returns true if edges connect all nodes
	
public:
protected:

	std::vector<Node *> m_nodes;

private:
};