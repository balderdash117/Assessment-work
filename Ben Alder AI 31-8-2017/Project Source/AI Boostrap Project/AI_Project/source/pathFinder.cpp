#include "pathFinder.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>


pathFinder::pathFinder(Graph2D * graph) : m_graph(graph), m_pathFound(false), m_goalNode(nullptr)
{

}

pathFinder::~pathFinder()
{
	for (auto iter = m_open.begin(); iter != m_open.end(); ++iter)
	{
		delete (*iter);
	}
	
	for (auto iter = m_closed.begin(); iter != m_closed.end(); ++iter)
	{
		delete (*iter);
	}

	m_open.clear();
	m_closed.clear();
}

Graph2D * pathFinder::getGraph()
{
	return m_graph;
}

path & pathFinder::getPath()
{
	return m_path;
}

void pathFinder::setGraph(Graph2D * graph)
{
	m_graph = graph;
}

void pathFinder::findPath(Graph2D::Node * startNode, std::function<bool(Graph2D::Node*)> goalNodeFunction)
{
	Node *node		= new Node();
	node->node		= startNode;
	node->gScore	= 0;
	node->hScore	= 0;
	node->fScore	= 0;
	node->parent	= nullptr;

	m_open.push_back(node);
	m_goalNodeFunction = goalNodeFunction;
	m_goalNode = nullptr;

	m_pathFound		= false;
}

void  pathFinder::findPath(Graph2D::Node *startNode, Graph2D::Node *goalNode)
{
	Node *node = new Node();
	node->node = startNode;
	node->gScore = 0;
	node->hScore = 0;
	node->fScore = 0;
	node->parent = nullptr;

	m_open.push_back(node);
	m_goalNodeFunction = std::function<bool(Graph2D::Node *)>(); 
	m_goalNode = goalNode;

	m_pathFound = false;
}

bool pathFinder::pathFound()
{
	return m_pathFound;
}

void pathFinder::updateSearch()
{
	if (m_open.empty())
	{
		m_pathFound = true;
	}

	if (m_pathFound == false)
	{
		//gets last node on open list
		Node *node = m_open.back();
		m_open.pop_back();
		m_closed.push_back(node);

		if (node->node == m_goalNode || (m_goalNodeFunction && m_goalNodeFunction(node->node)))
		{
			calculatePath(node);

			m_pathFound = true;
			return;
		}

		auto edges = node->node->edges;
		for (unsigned int i = 0; i < edges.size(); ++i)
		{
			Graph2D::Edge edge		= edges[i];
			Graph2D::Node *child	= edge.to;

			float cost				= edge.data;
			float gScore			= node->gScore + cost;
			float hScore			= 0;
			
			// if we're using astar
			if (m_goalNode)
			{
				hScore = glm::length2(m_goalNode->data - child->data);
			}
			
			float fScore = gScore + hScore;

			Node *nodeInList = getNodeInList(m_open, child);

			if (nodeInList == nullptr)
				nodeInList = getNodeInList(m_closed, child);

			if (nodeInList == nullptr)
			{
				Node *newNode = new Node();
				newNode->node = child;
				newNode->gScore = gScore;
				newNode->hScore = hScore;
				newNode->fScore = fScore;
				newNode->parent = node;

				m_open.push_back(newNode);
			}

			else
			{
				if (nodeInList->fScore > fScore)
				{
					nodeInList->parent = node;
					nodeInList->gScore = gScore;
					nodeInList->hScore = hScore;
					nodeInList->fScore = fScore;
				}
			}
		}

		m_open.sort([this](Node *a, Node *b) {
			return a->fScore > b->fScore;
		});

	}
}

pathFinder::Node *pathFinder::getNodeInList(std::list<Node*>& list, Graph2D::Node * node)
{
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		if ((*iter)->node == node)
			return (*iter);
	}

	return nullptr;
}

void pathFinder::calculatePath(Node * goal)
{
	m_path.clear();

	Node *current = goal;

	while (current != nullptr)
	{
		m_path.pushPathSegement(current->node->data);

		current = current->parent;
	}
}

