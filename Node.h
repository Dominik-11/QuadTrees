#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class Node
{
public:
	Node(Vector2f loc);

	void init();

	void tick();

	void render(RenderWindow& window);

	Vector2f location;

protected:

	CircleShape visualNode;

};

