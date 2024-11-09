#pragma once

#include "SFML/Graphics.hpp"
#include "Node.h"
#include <iostream>

using namespace sf;

struct NodeLList {
	Node &node;
	NodeLList *next = nullptr;
	//std::unique_ptr<NodeLList> next = nullptr;

	NodeLList(Node &newNode) : node(newNode) {}

	//becuse this is just a local list with references, when it goes out of scope it doesnt matter
	//i might want this tbh
	~NodeLList() {
		delete next;
	}
};

class QuadTree
{
public:
	QuadTree(Vector2f boundaryLocation, Vector2f boundarySize, int subdivideCapacity);
	~QuadTree();

	void init();

	void render(RenderWindow& window);

	void setBoundary(Vector2f boundaryLocation, Vector2f boundarySize);

	bool addNode(Node & newNode);

	void updateTree();

	//std::unique_ptr<NodeLList> query(FloatRect queryBounds);
	NodeLList* query(FloatRect queryBounds);

	void reset();

protected:

	void subdivide();

	void addNodeToSubdivision(Node& newNode);

	RectangleShape visualBoundary;
	FloatRect boundary;

	int capacity;

	std::unique_ptr<QuadTree> northWest = nullptr;
	std::unique_ptr<QuadTree> northEast = nullptr;
	std::unique_ptr<QuadTree> southWest = nullptr;
	std::unique_ptr<QuadTree> southEast = nullptr;

	std::unique_ptr<NodeLList> headNode = nullptr;

	//QuadTree* northWest = nullptr;
	//QuadTree* northEast = nullptr;
	//QuadTree* southWest = nullptr;
	//QuadTree* southEast = nullptr;

	//NodeLList* headNode = nullptr;

	bool treeSubdivided = false;

	//Node nodeArray[];

};

