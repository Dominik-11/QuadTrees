#include "Run.h"
#include <iostream>

Run::Run() : quadtree(Vector2f(10, 10), Vector2f(700, 700), 1)
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

	//addNewNode(Vector2f(300, 200));
	//addNewNode(Vector2f(400, 400));
	//addNewNode(Vector2f(70, 770));
	//addNewNode(Vector2f(770, 200));

	//addNewNode(Vector2f(310, 210));
	//addNewNode(Vector2f(410, 410));
	//addNewNode(Vector2f(80, 710));
	//addNewNode(Vector2f(780, 210));

	addNewBouncingNode(Vector2f(300, 200));
	addNewBouncingNode(Vector2f(400, 400));
	addNewBouncingNode(Vector2f(70, 770));
	addNewBouncingNode(Vector2f(770, 200));

	addNewBouncingNode(Vector2f(310, 210));
	addNewBouncingNode(Vector2f(410, 410));
	addNewBouncingNode(Vector2f(80, 710));
	addNewBouncingNode(Vector2f(780, 210));

	boundary.setPosition(bpos);
	boundary.setSize(bsize);
	boundary.setFillColor(Color::Transparent);
	boundary.setOutlineThickness(1.f);
	boundary.setOutlineColor(Color::Red);

	//FloatRect rect;
	//rect.left = bpos.x;
	//rect.top = bpos.y;
	//rect.width = bsize.x;
	//rect.height = bsize.y;

	//NodeLList* queryListHead = quadtree.query(rect);

	//if (queryListHead) {
	//	std::cout << queryListHead->node.location.x << ", " << queryListHead->node.location.y << "\n";
	//	queryListHead->node.visualNode.setFillColor(Color::Red);
	//}
	//else {
	//	return;
	//}

	//while (queryListHead->next) {
	//	queryListHead = queryListHead->next;
	//	std::cout << queryListHead->node.location.x << ", " << queryListHead->node.location.y << "\n";
	//	queryListHead->node.visualNode.setFillColor(Color::Red);
	//}

	//addBouncingNode(Vector2f(780, 210));
}

void Run::tick(float DeltaTime)
{
	quadtree.reset();

	MasterNodeLList* temp = headNode;

	while (temp) {
		temp->node->tick(DeltaTime);
		quadtree.addNode(*temp->node);
		temp = temp->next;
	}
	


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
		while (tempNode){
			tempNode->node->render(win);
			tempNode = tempNode->next;
		}
	}

	//win.draw(boundary);

}

void Run::addNewNode(Vector2f pos)
{
	//std::cout << "add node called\n";

	Node* newNode = new Node(pos);

	MasterNodeLList* newLLNode = new MasterNodeLList(newNode);

	if (!headNode) {
		headNode = newLLNode;
		quadtree.addNode(*newLLNode->node);
		return;
	}

	MasterNodeLList* temp = headNode;

	while (temp->next) {
		temp = temp->next;
	}

	temp->next = newLLNode;

	quadtree.addNode(*newLLNode->node);
}

void Run::addNewBouncingNode(Vector2f pos)
{
	BouncingNode* newNode = new BouncingNode(pos);

	MasterNodeLList* newLLNode = new MasterNodeLList(newNode);

	if (!headNode) {
		headNode = newLLNode;
		quadtree.addNode(*newLLNode->node);
		return;
	}

	MasterNodeLList* temp = headNode;

	while (temp->next) {
		temp = temp->next;
	}

	temp->next = newLLNode;

	quadtree.addNode(*newLLNode->node);
}

void Run::mousePressed(Vector2f location)
{
	addNewNode(location);
	//addBouncingNode(location);

}