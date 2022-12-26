#include <Button.hpp>


Button::Button()
{
    Button::status = 0;
}
int Button::getStatus()
{
    return Button::status;
}
Button::Button(std::string link)
{
    Button::status = 0;
    sf::Texture temp;
    temp.loadFromFile(link);
    Button::image.push_back(temp);
}

void Button::addImage(std::string link)
{
    sf::Texture temp;
    temp.loadFromFile(link);
    Button::image.push_back(temp);
}

sf::Sprite Button::getSprite()
{
    Button::position = sf::Vector2f(0, 0);
    return sf::Sprite(Button::image[Button::status]);
}

int Button::getW()
{
    return Button::image[Button::status].getSize().x;
}

int Button::getH()
{
    return Button::image[Button::status].getSize().y;
}

sf::Sprite Button::getSprite(float x, float y)
{
    Button::position = sf::Vector2f(x, y);
    sf::Sprite temp(Button::image[Button::status]);
    temp.setPosition(x, y);
    return temp;
}

sf::Sprite Button::getSprite(float x, float y, float c)
{
    Button::position = sf::Vector2f(x, y);
    sf::Sprite temp(Button::image[Button::status]);
    temp.setPosition(x, y);
    temp.scale(c, c);
    return temp;
}

bool Button::isMouseInside(float x, float y)
{
    if(x < Button::position.x || x > Button::position.x + Button::getW())
    {
        Button::status = 0;
        return 0;
    }
    if(y < Button::position.y || y > Button::position.y + Button::getH())
    {
        Button::status = 0;    
        return 0;
    }

    Button::status = 1;
    return 1;
}

void Button::setStatus(int value)
{
    Button::status = value;
}
