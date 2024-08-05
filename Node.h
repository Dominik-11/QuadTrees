#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

class Node
{
public:
	Node(Vector2f loc);

	void init();

	virtual void tick(float dt);

	void render(RenderWindow& window);

	Vector2f location;

	CircleShape visualNode;

protected:


};

