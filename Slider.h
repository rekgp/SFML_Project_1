#pragma once
#include <SFML/Graphics.hpp>
template<typename T>
class Slider : public sf::Drawable
{
public:
	Slider();
	Slider(void (*_func)(T));
	Slider(void (*_func)(T), const T &_max, const T &_min, const T &_step);

	void setPosition(const int &_x,const int &_y);
	void setPosition(const sf::Vector2f &_position);
	void setSize(const int &_x, const int &_y);
	void setSize(const sf::Vector2f &_size);
	void setFunction(void(*_func)(T));
	void setStep(const T &_step);
	void setMinMax(const T &_max,const T&_min = min);
	void check(const sf::Event &_event);
	void setValue(const T &_value);
	T getVelue();

	virtual void draw(sf::RenderTarget &render, sf::RenderStates states) const;
	
	std::unique_ptr<sf::Shape> outer, inner;
private:
	void (*func)(T);
	T value;
	T max, min, step;
	sf::Vector2f position, size;
	bool selected;
};

