#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Block : public Drawable
{
public:
    Block(float t_X, float t_Y, float t_Width, float t_Height);
    ~Block();
    void update();
    Vector2f getPosition();
    float left();
    float right();
    float top();
    float bottom();
    bool isDestroyed();
    void destroy();
    Vector2f getSize();
    virtual void draw(RenderTarget& target, RenderStates states) const override;

private:
    RectangleShape shape;
    bool destroyed{ false };
};

