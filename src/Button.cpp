#include <Button.hpp>

bool Button::isVisible()
{
    return !Button::invisible;
}

void Button::setVisible(bool visible)
{
    invisible = !visible;
}

int Button::getW()
{
    return Button::image[Button::status].getSize().x;
}

int Button::getH()
{
    return Button::image[Button::status].getSize().y;
}

Button::Button()
{
    Button::status = 0;
}

Button::Button(std::string link)
{
    Button::status = 0;
    Button::position = sf::Vector2f(0, 0);
    sf::Texture temp;
    temp.loadFromFile(link);
    Button::image.push_back(temp);
}

sf::Sprite Button::getSprite()
{
    sf::Sprite temp(Button::image[Button::status]);
    temp.setPosition(Button::position);
    return temp;
}

sf::Sprite Button::getSprite(float c)
{
    sf::Sprite temp(Button::image[Button::status]);
    temp.setPosition(Button::position.x, Button::position.y);
    temp.scale(c, c);
    return temp;
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

void Button::addImage(std::string link)
{
    sf::Texture temp;
    temp.loadFromFile(link);
    Button::image.push_back(temp);
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

int Button::getStatus()
{
    return Button::status;
}

void Button::setPosition(float x, float y)
{
    Button::position = sf::Vector2f(x, y);
}

void Button::setScreenID(int i)
{
    Button::ScreenID = i;
}

int Button::getScreenID()
{
    return Button::ScreenID;
}