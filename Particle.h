#pragma once
#include <SFML/Graphics.hpp>
#include "Vec3.h"
#include "Vec2.h"
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
    void setFlowField(const flowField& _flow);
    void update(sf::Time elapsed);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual Vec2f math(const Vec2f &_vec);

protected:
    Vec2<float> pos, vel;
    bool drawPart, drawTrail;
    sf::Shape* shape;
    sf::VertexArray trail;
    flowField& field;
};
