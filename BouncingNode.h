#pragma once

#include "Node.h"
#include <random>
#include <math.h>

class BouncingNode : public Node
{
public:

	BouncingNode(Vector2f loc);

	void tick(float dt);

protected:

	float moveAngle = 0.f;
	Vector2f moveVec;
	float speed = 10;

};

