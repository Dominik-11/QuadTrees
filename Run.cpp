#include "Run.h"
#include <iostream>

Run::Run() : quadtree(Vector2f(10, 10), Vector2f(700, 700), 2)
{
}

void Run::init() 
{
	//quadtree.init();
}

void Run::init(RenderWindow& win)
{
	//windowPosition = win.getPosition();

	quadtree.init();
	quadtree.setBoundary(Vector2f(10, 10), Vector2f(win.getSize().x - 20, win.getSize().y - 20));

	//std::cout << "bloody something!\n";

	addNode(Vector2f(300, 200));
	addNode(Vector2f(400, 400));
	addNode(Vector2f(70, 770));
	addNode(Vector2f(770, 200));

	addNode(Vector2f(310, 210));
	addNode(Vector2f(410, 410));
	addNode(Vector2f(80, 710));
	addNode(Vector2f(780, 210));
}

void Run::tick(float DeltaTime)
{

	//if (windowPosition.x < 500 && switchways == -1) {
	//	switchways = 1;
	//}
	//else if (windowPosition.x > 1000 && switchways == 1) {
	//	switchways = -1;
	//}

	//windowPosition.x = windowPosition.x + (speed * switchways);
	//win.setPosition(windowPosition);

	//std::cout << windowPosition.x << "\n";


}

void Run::render(RenderWindow& win)
{
	quadtree.render(win);

	if (headNode) {
		MasterNodeLList* tempNode = headNode;
		while (tempNode) {
			tempNode->node.render(win);
			tempNode = tempNode->next;
		}
	}

}

void Run::addNode(Vector2f pos)
{
	//std::cout << "add node called\n";

	Node newNode(pos);

	MasterNodeLList* newLLNode = new MasterNodeLList(newNode);

	if (!headNode) {
		headNode = newLLNode;
		quadtree.addNode(newLLNode->node);
		return;
	}

	MasterNodeLList* temp = headNode;

	while (temp->next) {
		temp = temp->next;
	}

	temp->next = newLLNode;

	quadtree.addNode(newLLNode->node);

}
