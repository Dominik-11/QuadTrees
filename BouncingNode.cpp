#include "BouncingNode.h"

BouncingNode::BouncingNode(Vector2f loc) : Node(loc)
{
	//moveAngle = rand() % 361;

	//float moveAngleRad = moveAngle *  3.14159f / 180.0f;

	moveVec = Vector2f(cos(moveAngle), sin(moveAngle));

	//std::cout << moveVec.x << " ," << moveVec.y << "\n";

}

void BouncingNode::tick(float dt)
{
	//std::cout << "BTick!\n";

	//Node::tick(dt);
	
	location = location + (moveVec * (speed * dt));
	visualNode.setPosition(location);


	//std::cout << location.x << " ," << location.y << "\n";


}
