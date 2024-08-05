
#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include "Run.h"

using namespace sf;

int main() {

	RenderWindow window(VideoMode(800, 800), "Octrees");
	Event e;

	Clock clock;
	float deltaTime = 0;

	Run run;
	run.init(window);

	Mouse mouse;

	bool mouseDown = false;
	float mouseDrawIntervalTime = 0.1f;
	float mouseDrawInterval = 0.f;

	while (window.isOpen()) {
		while (window.pollEvent(e)) {

			switch (e.type) {
			case Event::Closed:
				window.close();
				return 0;
			case Event::MouseButtonPressed:
				mouseDown = true;
				//std::cout << "pressed\n";
				break;
			case Event::MouseButtonReleased:
				mouseDown = false;
				//std::cout << "released\n";
				break;
			}
		}

		if (mouseDown) {
			mouseDrawInterval += deltaTime;
			if (mouseDrawInterval > mouseDrawIntervalTime) {
				//run.mousePressed(Vector2f(e.mouseButton.x, e.mouseButton.y));
				run.mousePressed(Vector2f(mouse.getPosition(window).x, mouse.getPosition(window).y));
				mouseDrawInterval = 0;
			}
		}

		//mouse.getPosition(window);

		run.tick(deltaTime);

		deltaTime = clock.restart().asSeconds();

		window.clear(Color::Color(37, 150,190));

		run.render(window);

		window.display();
	}

	return 0;
}