
#include "SFML/Graphics.hpp"
#include "Run.h"

using namespace sf;

int main() {

	RenderWindow window(VideoMode(800, 800), "Octrees");
	Event e;

	Clock clock;
	float deltaTime = 0;

	Run run;
	run.init(window);

	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}

		run.tick(deltaTime);

		deltaTime = clock.restart().asSeconds();

		window.clear(Color::Color(37, 150,190));

		run.render(window);

		window.display();
	}

	return 0;
}