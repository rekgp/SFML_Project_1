#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Vec3.h"
#include "PerlinNoise.h"
#include "Slider.h"
#include "flowField.h"

using namespace std;

const int window_width = 800;
const int window_height = 600;

int main() {
	std::cout << "Hello world" << std::endl;

	//window setup
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Projekt Koncowy");

	sf::Clock clock;

	PerlinNoise noise;

	flowField flowfield(&window,5,5,2022);
	flowfield.setDrawable(1);

	sf::Image img;
	img.create(500, 500);
	Vec3f deriv(0,0,0);
	for(unsigned int x = 1; x < 500; x++){
		for (unsigned int y = 1; y < 500; y++) {
			sf::Uint8 value = std::floor((noise.eval(Vec3f((float)x/50, (float)y/50, (float)1/50), deriv)+1)/2*255);
			img.setPixel(x, y, sf::Color(value,value,value));
			if (x == 10) {
				//std::cout << noise.eval(Vec3f((float)x / 50, (float)y / 50, (float)1 / 50), deriv) << std::endl;
				//std::cout << deriv.x << ", " << deriv.y << ", " << deriv.z << std::endl;
			}
			if (x > 250) {
				img.setPixel(x, y, sf::Color((deriv.x + 1)/2*255, (deriv.y + 1) / 2 * 255, (deriv.z + 1) / 2 * 255));
			}
		}
	}
	for (unsigned int x = 0; x < 500; x++) {
		img.setPixel(x, 1, sf::Color::Yellow);
	}

	sf::Texture texture;
	texture.loadFromImage(img);

	sf::RectangleShape rect;
	rect.setPosition(300, 75);
	//rect.setFillColor(sf::Color::Red);
	rect.setTexture(&texture);
	rect.setSize(sf::Vector2f(500,500));

	Slider<float,sf::RectangleShape,void (sf::RectangleShape::*)(float)> slider(rect,&sf::RectangleShape::setRotation);
	slider.setMinMax(360.0, 0.0);
	slider.setPosition(sf::Vector2f(300, 50));
	slider.setSize(sf::Vector2f(200, 50));
	slider.setFillColor(sf::Color::Red, sf::Color::Blue);

	

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
			if (event.type == sf::Event::MouseWheelMoved) {
				rect.setRotation(rect.getRotation() + event.mouseWheel.delta);
			}
			slider.check(event,window);
			
		}
		// per frame calculations


		//draw everyting
		window.clear(sf::Color::Black);

		window.draw(rect);
		window.draw(slider);
		window.draw(flowfield);
		window.display();

	}

	return 0;
}