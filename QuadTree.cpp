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

bool QuadTree::addNode(Node & newNode)
{
	//std::cout << "add node\n";

	if (!boundary.contains(newNode.location)) {
		return false;
	}

	if (treeSubdivided) {
		addNodeToSubdivision(newNode);
		return true;
	}

	//NodeLList* newLLNode = new NodeLList(newNode);
	//NodeLList* newLLNode = std::make_unique<NodeLList>(newNode);
	// std::unique_ptr<NodeLList> newLLNode = std::make_unique<NodeLList>(newNode);
	std::unique_ptr<NodeLList> newLLNode(new NodeLList(newNode));

	if (!headNode) {
		//std::cout << "added to head\n";
		//headNode = std::make_unique<NodeLList>(newNode);
		headNode = std::move(newLLNode);
		return true;
	}

	//std::unique_ptr<NodeLList> temp = std::make_unique<NodeLList>(headNode);
	//std::unique_ptr<NodeLList> temp(headNode);
	NodeLList* temp = headNode.get();

	int LCount = 2;
	while (temp->next) {
		temp = temp->next.get();
		LCount++;
	}

	if (LCount > capacity) {

		//std::cout << "count was " << LCount << "\n";

		subdivide();

		temp = headNode.get();
		while (temp) {
			addNodeToSubdivision(temp->node);
			temp = temp->next.get();
		}
		//delete headNode;
		//headNode = nullptr;
		headNode.reset();

		addNodeToSubdivision(newNode);
		return true;
	}

	temp->next = std::move(newLLNode);
}

void QuadTree::updateTree()
{
	//delete all subtrees

	//if (treeSubdivided) {
	//	northWest->updateTree();
	//	northEast->updateTree();
	//	southWest->updateTree();
	//	southEast->updateTree();
	//}

}

NodeLList* QuadTree::query(FloatRect queryBounds)
{
	if (!boundary.intersects(queryBounds)) {
		return nullptr;
	}

	//if not subdevided ypure at the end, grab the nodes and leave
	if (!treeSubdivided) {
		return headNode.get();
	}

	NodeLList* nodesFound = nullptr;

	//recurse to next layer
	NodeLList* foundNodes[4];

	foundNodes[0] = northWest->query(queryBounds);
	foundNodes[1] = northEast->query(queryBounds);
	foundNodes[2] = southWest->query(queryBounds);
	foundNodes[3] = southEast->query(queryBounds);

	for (NodeLList* foundList : foundNodes) {
		if (foundList) {
			if (!nodesFound) {
				nodesFound = foundList;
			}
			else {
				NodeLList* temp = nodesFound;
				while (temp->next) {
					temp = temp->next.get();
				}
				temp->next = foundList;
			}
		}
	}

	return nodesFound;
}

void QuadTree::reset()
{
	//delete all bar this one
	//after adding this it started to work but theres a boy memory leak somewhere, i think its just fast cos its in tick


	//if (treeSubdivided) {
	//	delete northWest, northEast, southEast, southWest, headNode;
	//	headNode = nullptr;
	//	treeSubdivided = false;
	//}

	//if (treeSubdivided) {
	//	delete northWest, northEast, southEast, southWest;
	//	treeSubdivided = false;
	//}
}

void QuadTree::subdivide()
{
	//std::cout << "subdivide!\n";

	Vector2f size = Vector2f(boundary.getSize().x / 2, boundary.getSize().y / 2);

	Vector2f nwLoc = boundary.getPosition();
	northWest = std::make_unique<QuadTree>(nwLoc, size, capacity);
	//northWest = new QuadTree(nwLoc, size, capacity);

	Vector2f neLoc = Vector2f(boundary.getPosition().x + (boundary.getSize().x / 2), boundary.getPosition().y);
	northEast = std::make_unique<QuadTree>(nwLoc, size, capacity);
	//northEast = new QuadTree(neLoc, size, capacity);

	Vector2f swLoc = Vector2f(boundary.getPosition().x, boundary.getPosition().y + (boundary.getSize().y / 2));
	southWest = std::make_unique<QuadTree>(nwLoc, size, capacity);
	//southWest = new QuadTree(swLoc, size, capacity);

	Vector2f seLoc = Vector2f(boundary.getPosition().x + (boundary.getSize().x / 2), boundary.getPosition().y + (boundary.getSize().y / 2));
	southEast = std::make_unique<QuadTree>(nwLoc, size, capacity);
	//southEast = new QuadTree(seLoc, size, capacity);

	treeSubdivided = true;
}


void QuadTree::addNodeToSubdivision(Node& newNode)
{
	if (!treeSubdivided) {
		std::cout << "ERROR addNodeToSubdivision called while tree not subdivided \n";
		return;
	}

	//std::cout << "added to subtree\n";

	if (northWest->addNode(newNode) ||
		northEast->addNode(newNode) ||
		southWest->addNode(newNode) ||
		southEast->addNode(newNode)) 
	{
		return;
	}
}

QuadTree::~QuadTree()
{
	//delete northWest, northEast, southWest, southEast, headNode;
}