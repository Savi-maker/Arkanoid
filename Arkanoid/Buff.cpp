#include "Buff.h"

Buff::Buff(float t_X, float t_Y, BuffType t_type)
    : type(t_type), active(true)
{
    shape.setPosition(t_X, t_Y);
    shape.setRadius(10.0f);
    shape.setFillColor(Color::Yellow);
    shape.setOrigin(10.0f, 10.0f);
}

Buff::Buff(const Buff& other)
    : shape(other.shape), type(other.type), active(other.active), clock(other.clock), duration(other.duration)
{
}

Buff& Buff::operator=(const Buff& other)
{
    if (this != &other)
    {
        shape = other.shape;
        type = other.type;
        active = other.active;
        clock = other.clock;
        // duration jest const, wiêc nie trzeba go przypisywaæ
    }
    return *this;
}

void Buff::update()
{
    if (clock.getElapsedTime().asSeconds() >= duration)
    {
        active = false;
    }
}

bool Buff::isActive() const
{
    return active;
}

BuffType Buff::getType() const
{
    return type;
}

float Buff::left() const
{
    return shape.getPosition().x - shape.getRadius();
}

float Buff::right() const
{
    return shape.getPosition().x + shape.getRadius();
}

float Buff::top() const
{
    return shape.getPosition().y - shape.getRadius();
}

float Buff::bottom() const
{
    return shape.getPosition().y + shape.getRadius();
}

void Buff::draw(RenderTarget& target, RenderStates state) const
{
    if (active)
    {
        target.draw(shape, state);
    }
}
