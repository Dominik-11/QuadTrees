#pragma once

#include "SFML/Graphics.hpp"
#include "Node.h"
#include <iostream>

using namespace sf;

struct NodeLList {
	Node &node;
	NodeLList *next = nullptr;

	NodeLList(Node &newNode) : node(newNode) {}

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

	void addNode(Node & newNode);

protected:

	void subdivide();

	void addNodeToSubdivision(Node& newNode);

	RectangleShape visualBoundary;
	FloatRect boundary;

	int capacity;

	QuadTree* northWest = nullptr;
	QuadTree* northEast = nullptr;
	QuadTree* southWest = nullptr;
	QuadTree* southEast = nullptr;

	NodeLList* headNode = nullptr;

	bool treeSubdivided = false;

	//Node nodeArray[];

};

