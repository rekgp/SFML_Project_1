#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Vec3.h"
#include "PerlinNoise.h"
#include "Slider.h"
#include "flowField.h"
#include "Particle.h"

using namespace std;

const int window_width = 800;
const int window_height = 600;

int main() {
	std::cout << "Hello world" << std::endl;

	//window setup
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Projekt Koncowy");

	sf::Clock clock;

	flowField flowfield(&window,10,10,2022);
	flowfield.setDrawable(1);
	flowfield.setAnimation(1);
	flowfield.setAnimationSpeed(0.5);
	flowfield.setScale(0.09);

	Particle atoms(flowfield);
	atoms.shape = new sf::RectangleShape(sf::Vector2f(5, 5));
	atoms.setParticleDrawing(1);
	atoms.setTrailDrawing(1);
	atoms.setMaxSpeed(40.0);
	atoms.setWindow(&window);
	

	//main loop
	while (window.isOpen()) {
		sf::Time elapsed = clock.restart();

		//event handling
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Closing Window" << std::endl;
				window.close();
			}
			
		}
		// per frame calculations

		flowfield.update(elapsed);
		atoms.update(elapsed);
		//draw everyting
		window.clear(sf::Color::Black);

		window.draw(flowfield);
		window.draw(atoms);
		window.display();

	}

	return 0;
}