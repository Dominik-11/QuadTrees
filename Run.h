#pragma once

#include "SFML/Graphics.hpp"
#include "QuadTree.h"
#include "Node.h"
#include "BouncingNode.h"

using namespace sf;

struct MasterNodeLList {
	Node* node;
	MasterNodeLList* next = nullptr;

	MasterNodeLList(Node* newNode) : node(newNode) {}

	~MasterNodeLList() {
		delete next, node;
	}
};

//struct MaterListtwo : public MasterNodeLList {
//
//};

class Run
{
public:
	Run();

	void init();
	void init(RenderWindow& win);

	void tick(float dt);

	void render(RenderWindow& win);

	void addNode(Vector2f pos);

	void addBouncingNode(Vector2f pos);

	void mousePressed(Vector2f location);

protected:
	//Int8 switchways = 1;
	//Int16 speed = 1;
	//Vector2i windowPosition = Vector2i(800, 800);

	QuadTree quadtree;
	MasterNodeLList* headNode = nullptr;

	//Node* nodes[];

	RectangleShape boundary;
	Vector2f bsize = Vector2f(300, 300);
	Vector2f bpos = Vector2f(180, 180);

};

