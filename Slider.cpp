#include "Slider.h"
template<typename T>
inline Slider<T>::Slider() {}

template<typename T>
Slider<T>::Slider(void(*_func)(T)) : func(_func) {}

template<typename T>
Slider<T>::Slider(void(*_func)(T), const T &_max, const T &_min, const T &_step) : func(_func), max(_max), min(_min), step(_step) {};

template<typename T>
void Slider<T>::setPosition(const int &_x, const int &_y) {
	this->position = sf::Vector2f(_x, _y);
}

template<typename T>
void Slider<T>::setPosition(const sf::Vector2f &_position) {
	this->position = _position;
}

template<typename T>
void Slider<T>::setSize(const int &_x, const int &_y) {
	this->size = sf::Vector2f(_x, _y);
}

template<typename T>
void Slider<T>::setSize(const sf::Vector2f &_size) {
	this->size = _size;
}

template<typename T>
void Slider<T>::setFunction(void(*_func)(T)) {
	func = _func;
}

template<typename T>
void Slider<T>::setStep(const T &_step) {
	step = _step;
}

template<typename T>
void Slider<T>::setMinMax(const T &_max, const T &_min) {
	this->min = _min;
	this->max = _max;
}

template<typename T>
void Slider<T>::check(const sf::Event &_event) {
	if (_event == sf::Event::MouseButtonPressed) {
		auto bounds = inner->getGlobalBounds();
		auto mouse = sf::Mouse::getPosition();
		if (mouse.x > bounds.left && mouse.x < bounds.left + bounds.width) {
			if (mouse.y > bounds.top && mouse.y < bounds.top + bounds.height) {
				inner->setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
			}
		}
	}
}

