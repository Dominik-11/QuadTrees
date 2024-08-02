#include "QuadTree.h"

QuadTree::QuadTree(Vector2f loc, Vector2f size, int cap) : capacity(cap)
{
	boundary.left = loc.x;
	boundary.top = loc.y;
	boundary.width = size.x;
	boundary.height = size.y;

	visualBoundary.setPosition(loc);
	visualBoundary.setSize(size);
	visualBoundary.setFillColor(Color::Transparent);
	visualBoundary.setOutlineThickness(1.f);
	visualBoundary.setOutlineColor(Color::Black);
}

void QuadTree::init()
{
}

void QuadTree::render(RenderWindow& window)
{
	window.draw(visualBoundary);

	if (treeSubdivided) {
		northWest->render(window);
		northEast->render(window);
		southWest->render(window);
		southEast->render(window);
	}
}

void QuadTree::setBoundary(Vector2f loc, Vector2f size)
{
	boundary.left = loc.x;
	boundary.top = loc.y;
	boundary.width = size.x;
	boundary.height = size.y;

	visualBoundary.setPosition(loc);
	visualBoundary.setSize(size);
}

void QuadTree::addNode(Node & newNode)
{
	//std::cout << "quadtree add node called\n";

	if (!boundary.contains(newNode.location)) {
		return;
	}

	if (treeSubdivided) {
		addNodeToSubdivision(newNode);
		return;
	}

	NodeLList* newLLNode = new NodeLList(newNode);

	if (!headNode) {
		std::cout << "added to head\n";
		headNode = newLLNode;
		return;
	}

	NodeLList* temp = headNode;

	int LCount = 1;
	while (temp->next) {
		temp = temp->next;
		LCount++;
	}

	if (LCount > capacity) {

		std::cout << "count was " << LCount << "\n";


		subdivide();
		addNodeToSubdivision(newNode);
		return;
	}

	temp->next = newLLNode;
}

void QuadTree::subdivide()
{
	std::cout << "subdivide!\n";

	Vector2f size = Vector2f(boundary.getSize().x / 2, boundary.getSize().y / 2);

	Vector2f nwLoc = boundary.getPosition();
	northWest = new QuadTree(nwLoc, size, capacity);

	Vector2f neLoc = Vector2f(boundary.getPosition().x + (boundary.getSize().x / 2), boundary.getPosition().y);
	northEast = new QuadTree(neLoc, size, capacity);

	Vector2f swLoc = Vector2f(boundary.getPosition().x, boundary.getPosition().y + (boundary.getSize().y / 2));
	southWest = new QuadTree(swLoc, size, capacity);

	Vector2f seLoc = Vector2f(boundary.getPosition().x + (boundary.getSize().x / 2), boundary.getPosition().y + (boundary.getSize().y / 2));
	southEast = new QuadTree(seLoc, size, capacity);

	treeSubdivided = true;
}


void QuadTree::addNodeToSubdivision(Node& newNode)
{
	if (!treeSubdivided) {
		std::cout << "ERROR addNodeToSubdivision called while tree not subdivided \n";
		return;
	}

	std::cout << "added to body\n";


	northWest->addNode(newNode);
	northEast->addNode(newNode);
	southWest->addNode(newNode);
	southEast->addNode(newNode);
}

QuadTree::~QuadTree()
{
	delete northWest, northEast, southWest, southEast, headNode;
}