#pragma once
#include <SFML/Graphics.hpp>
#include "Vec3.h"
#include "flowField.h"

class Particle :
    public sf::Drawable
{
public:
    Particle();
    virtual ~Particle();

    void setParticleDrawing(bool _drawPart);
    void setTrailDrawing(bool _drawTrail);
    void setParticleShape(const sf::Shape& _shape);
    virtual void update(const flowField &_flowfield);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


protected:
    Vec2<float> pos, vel;
    bool drawPart, drawTrail;
    sf::Shape* shape;
    sf::VertexArray trail;
};
