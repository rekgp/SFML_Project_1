#include "Particle.h"

void Particle::setParticleDrawing(bool _drawPart)
{
	drawPart = _drawPart;
}

void Particle::setTrailDrawing(bool _drawTrail)
{
	drawTrail = _drawTrail;
}

void Particle::setParticleShape(const sf::Shape& _shape)
{
	*shape = _shape;
}

void Particle::setFlowField(const flowField& _flow)
{
	field = _flow;
}

void Particle::update(sf::Time elapsed)
{
	vel = vel + math(field.getVelocityVector(pos));
	pos = pos + vel * elapsed.asSeconds();
	shape->setPosition(sf::Vector2f(pos.x, pos.y));

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
