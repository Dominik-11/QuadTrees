#include "Node.h"

Node::Node(Vector2f loc)
{
	location = loc;

	visualNode.setRadius(4.f);
	visualNode.setPosition(loc);
	visualNode.setFillColor(Color::Black);
}

void Node::init()
{

}

void Node::tick(float dt)
{
	
}

void Node::render(RenderWindow& window)
{
	window.draw(visualNode);
}
