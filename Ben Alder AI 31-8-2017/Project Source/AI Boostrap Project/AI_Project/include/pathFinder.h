#pragma once

#include "graph2DRenderer.h"
#include "path.h"

#include <functional>
#include <list>

class path;

class pathFinder
{
public:
											 pathFinder(Graph2D *graph);
											~pathFinder();
											
	Graph2D									*getGraph();
	path									&getPath();

	void									 setGraph(Graph2D *graph);
											 
	void									 findPath(Graph2D::Node *startNode, std::function<bool(Graph2D::Node *)> goalNodeFunction);
											 
	void									 findPath(Graph2D::Node *startNode, Graph2D::Node *goalNode);


	bool									 pathFound();
											 
	void									 updateSearch();

protected:

	struct Node
	{
		Graph2D::Node						*node = nullptr;
		Node								*parent = nullptr;

		float								 gScore;
		float								 fScore;
		float								 hScore;
	};

	Graph2D									*m_graph;
	std::function<bool(Graph2D::Node *)>	 m_goalNodeFunction; // for dijkstras
	Graph2D::Node							*m_goalNode; // for astar
	bool									 m_pathFound;
	path									 m_path;

	std::list<Node *>						 m_open;
	std::list<Node *>						 m_closed;

	

private:

	Node									*getNodeInList(std::list<Node*> &list,Graph2D::Node *node);
	void									 calculatePath(Node *goal);

public:

	const std::list<Node *> &GetOpen() const { return m_open; }
	const std::list<Node *> &GetClosed() const { return m_closed; }
};

