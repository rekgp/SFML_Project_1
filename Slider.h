#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

template<typename T, typename Object, typename Method>
class Slider : public sf::Drawable
{
public:
	Slider();
	Slider(Object &_obj, Method mp);
	Slider(Object &_obj, Method mp,const T &_max, const T &_min, const T &_step);

	void setPosition(const int &_x,const int &_y);
	void setPosition(const sf::Vector2f &_position);
	void setSize(const int &_x, const int &_y);
	void setSize(const sf::Vector2f &_size);
	void setFunction(Method mp);
	void setStep(const T &_step);
	void setMinMax(const T &_max,const T&_min = min);
	void check(const sf::Event &_event, const sf::RenderWindow &_window);
	void setValue(const T &_value);
	void setFillColor(const sf::Color &_inner, const sf::Color &_outer);
	void setObj(const Object &_obj);
	T getVelue();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
	Object *obj;
	Method pnt;
private:
	T value = 50;
	T max = 100, min = 0, step = 1;
	sf::Vector2f position, size;
	bool selected = 0;
	sf::RectangleShape inner, outer;
	const float padding = 10;

	void setInnerPosition();
};

template<typename T, typename Object, typename Method>
inline Slider<T,Object,Method>::Slider() {
}

template<typename T, typename Object, typename Method>
inline Slider<T,Object,Method>::Slider(Object &_obj, Method mp) {
	obj = &_obj;
	pnt = mp;
}

template<typename T, typename Object, typename Method>
void Slider<T,Object,Method>::setPosition(const int &_x, const int &_y) {
	this->position = sf::Vector2f(_x, _y);
	this->outer.setPosition(this->position);
	setInnerPosition();
}

template<typename T, typename Object, typename Method>
void Slider<T,Object,Method>::setPosition(const sf::Vector2f &_position) {
	this->position = _position;
	this->outer.setPosition(this->position);
	setInnerPosition();
}

template<typename T, typename Object, typename Method>
void Slider<T,Object,Method>::setSize(const int &_x, const int &_y) {
	this->size = sf::Vector2f(_x, _y);
	this->outer.setSize(this->size);
	this->inner.setSize(sf::Vector2f(this->size.y - 2 * this->padding, this->size.y - 2 * this->padding));
	setInnerPosition();
}

template<typename T, typename Object, typename Method>
void Slider<T,Object,Method>::setSize(const sf::Vector2f &_size) {
	this->size = _size;
	this->outer.setSize(this->size);
	this->inner.setSize(sf::Vector2f(this->size.y - 2 * this->padding, this->size.y - 2 * this->padding));
	setInnerPosition();
}

template<typename T, typename Object, typename Method>
void Slider<T,Object,Method>::setFunction(Method mp) {
	pnt = mp;
}

template<typename T, typename Object, typename Method>
void Slider<T,Object,Method>::setStep(const T &_step) {
	step = _step;
}

template<typename T, typename Object, typename Method>
void Slider<T,Object,Method>::setMinMax(const T &_max, const T &_min) {
	this->min = _min;
	this->max = _max;
}

template<typename T, typename Object, typename Method>
void Slider<T,Object,Method>::check(const sf::Event &_event,const sf::RenderWindow &_window) {
	if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left) {
		auto bounds = inner.getGlobalBounds();
		auto mouse = sf::Mouse::getPosition(_window);
		std::cout << mouse.x << ", " << mouse.y << std::endl;
		if (mouse.x > bounds.left && mouse.x < bounds.left + bounds.width) {
			if (mouse.y > bounds.top && mouse.y < bounds.top + bounds.height) {
				std::cout << "inner clicked" << std::endl;
				selected = true;
			}
		}
	}
	if (_event.type == sf::Event::MouseMoved && selected) {
		auto x = sf::Mouse::getPosition(_window).x;
		float left = this->position.x + this->padding + this->inner.getSize().x/2;
		float right = this->position.x + this->size.x - this->padding - this->inner.getSize().x/2;
		float relative = (x-left)/(right-left);
		if (relative >= 0.0 && relative <= 1.0) {
			this->setValue((T)(this->max * relative));
		}
		else if (relative > 1.0) {
			this->setValue(this->max);
		}
		else if (relative < 0.0) {
			this->setValue(this->min);
		}
	}
	if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left) {
		selected = false;
	}
}

template<typename T, typename Object, typename Method>
inline void Slider<T,Object,Method>::setValue(const T &_value) {
	value = _value;
	(obj->*pnt)(value);
	setInnerPosition();
}

template<typename T, typename Object, typename Method>
inline void Slider<T,Object,Method>::setFillColor(const sf::Color &_inner, const sf::Color &_outer) {
	inner.setFillColor(_inner);
	outer.setFillColor(_outer);
}

template<typename T, typename Object, typename Method>
inline T Slider<T,Object,Method>::getVelue() {
	return value;
}

template<typename T, typename Object, typename Method>
void Slider<T,Object,Method>::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(outer);
	target.draw(inner);
}

template<typename T, typename Object, typename Method>
inline void Slider<T,Object,Method>::setInnerPosition() {
	float left = this->position.x + this->padding + this->inner.getSize().x / 2;
	float right = this->position.x + this->size.x - this->padding - this->inner.getSize().x / 2;
	inner.setPosition(sf::Vector2f(
		this->position.x + this->padding + ((float)this->value/this->max)*(right - left),
		this->position.y + this->padding
	));
	std::cout << inner.getPosition().x << ", " << inner.getPosition().y << std::endl;
}
