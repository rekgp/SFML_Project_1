#pragma once
#include <SFML/Graphics.hpp>
#include "Vec3.h"
#include "Vec2.h"
#include "flowField.h"

class Particle :
    public sf::Drawable
{
public:
    Particle(flowField& flow);
    virtual ~Particle();

    void setParticleDrawing(bool _drawPart);
    void setTrailDrawing(bool _drawTrail);
    void setFlowField(const flowField& _flow);
    void setMaxSpeed(const float& _max);
    void update(sf::Time elapsed);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual Vec2f math(const Vec2f &_vec);

    void setWindow(sf::RenderWindow* _window);


    sf::Shape* shape;
protected:
    Vec2<float> pos, vel;
    bool drawPart, drawTrail;
    sf::VertexArray trail;
    flowField& field;
    float maxspeed;
    sf::RenderWindow* window;
};
