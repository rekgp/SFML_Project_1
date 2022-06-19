#pragma once
#include "PerlinNoise.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Vec3.h"
#include "Vec2.h"

class flowField : public sf::Drawable
{
public:
	flowField(sf::RenderWindow *_window,const int &_nx,const int &_ny,const unsigned &seed);
	~flowField();
	
	void setWindow(sf::RenderWindow *_window);
	void setScale(const float &_scale);
	void setXnumber(const int &_nx);
	void setYnumber(const int &_ny);
	void setNewSeed(const unsigned &seed);
	void setAnimation(const bool &_arg);
	void setAnimationSpeed(const float& _speed);
	void setDrawable(const bool& _arg);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time);
	Vec2f getVelocityVector(const Vec3f& _pos);

private:
	std::vector <std::vector<std::pair<Vec2f,float>>> grid;
	sf::RenderWindow *window;
	PerlinNoise noise;
	int nx, ny;
	float scale;
	
	bool visualize;
	std::vector<std::vector<sf::RectangleShape>> visualVectors;


	float ySpeed;
	bool yAnimation;
	
	void recalc();
	void resize();
};

