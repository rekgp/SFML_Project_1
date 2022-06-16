#pragma once
#include "PerlinNoise.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "vec3.h"
#include "vec2.h"

class flowField : public sf::Drawable
{
public:
	flowField();
	
	void setDencity();
	void setNewSeed();
	bool setDrawable(const bool& _arg);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update();
	Vec2<float> getNearestVec(const Vec3f& _pos);

private:
	PerlinNoise noise;
	std::vector <std::vector<Vec3f>> grid;
};

