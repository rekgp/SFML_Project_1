#include "Particle.h"


Particle::Particle(flowField& flow) : field(flow)
{
	pos = Vec2f(10, 10);
	vel = Vec2f(0, 0);
}

Particle::~Particle()
{
}

void Particle::setParticleDrawing(bool _drawPart)
{
	drawPart = _drawPart;
}

void Particle::setTrailDrawing(bool _drawTrail)
{
	drawTrail = _drawTrail;
}

void Particle::setFlowField(const flowField& _flow)
{
	field = _flow;
}

void Particle::setMaxSpeed(const float& _max)
{
	maxspeed = _max;
}

void Particle::update(sf::Time elapsed)
{
	vel = math(field.getVelocityVector(pos));
	pos = pos + (vel * maxspeed * elapsed.asSeconds());
	//std::cerr << "Vel= " << vel.x << ", " << vel.y << "Pos= " << pos.x << ", " << pos.y << std::endl;
	auto windowSize = window->getSize();
	if (pos.x < 0) {
		pos.x = windowSize.x;
	}
	else if (pos.x > windowSize.x) {
		pos.x = 0;
	}
	if (pos.y < 0) {
		pos.y = windowSize.y;
	}
	else if (pos.y > windowSize.y) {
		pos.y = 0;
	}
	
	shape->setPosition(sf::Vector2f(pos.x, pos.y));

	if (drawTrail) {
		//do the thing iwth the traingle strips or something
	}
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (drawPart) {
		target.draw(*shape);
	}
	if (drawTrail) {
		target.draw(trail);
	}

}

Vec2f Particle::math(const Vec2f& _vec)
{
	Vec2f var = vel + Vec2f(_vec.x * 0.1,_vec.y * 0.1);
	//std::cerr << "normalized vec " << var.x << ", " << var.y << std::endl;
	var.normalize();
	var* maxspeed;
	return var;
}

void Particle::setWindow(sf::RenderWindow* _window)
{
	window = _window;
}
