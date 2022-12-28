#include <InputBox.hpp>

InputBox::InputBox()
{
    background.setSize(sf::Vector2f(180, 60));
    background.setFillColor(sf::Color(0, 128, 255));
    inp = 0;
    focus = false;
    
    title.setFont(GraphicsData::font);
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);

    num.setFont(GraphicsData::font);
    num.setCharacterSize(48);
    num.setFillColor(sf::Color::White);
    num.setString("0");
}

void InputBox::setPosition(float x, float y)
{
    background.setPosition(x + 480 , y - 15);
    num.setPosition(x + 510, y - 20);
    title.setPosition(x, y); 
}

void InputBox::setTitle(std::string s)
{   
    title.setString(s);
}

bool InputBox::isMouseInside(int x, int y)
{
    if(x < background.getPosition().x || background.getPosition().x + background.getSize().x <= x) 
        return false;
    if(y < background.getPosition().y || background.getPosition().y + background.getSize().y <= y)
        return false;
    return true;
}

void InputBox::setFocus(bool isFocus)
{
    focus = isFocus;
    if(focus) background.setFillColor(sf::Color(128, 128, 255));
    else background.setFillColor(sf::Color(0, 128, 255));
}

bool InputBox::addDigit(int d)
{
    if(!focus) return false;
    if(inp * 10 + d > 100) return false;
    if(d < 0 || d > 9) return false;
    inp = inp * 10 + d;
    num.setString(std::to_string(inp));
    return true;
}

void InputBox::typing(sf::Keyboard::Key code)
{
    if(!focus) return ;

    switch(code)
    {
        case sf::Keyboard::BackSpace:
            pop();
            break;
        case sf::Keyboard::Num0:
            addDigit(0);
            break;
        case sf::Keyboard::Num1:
            addDigit(1);
            break;
        case sf::Keyboard::Num2:
            addDigit(2);
            break;
        case sf::Keyboard::Num3:
            addDigit(3);
            break;
        case sf::Keyboard::Num4:
            addDigit(4);
            break;
        case sf::Keyboard::Num5:
            addDigit(5);
            break;
        case sf::Keyboard::Num6:
            addDigit(6);
            break;
        case sf::Keyboard::Num7:
            addDigit(7);
            break;
        case sf::Keyboard::Num8:
            addDigit(8);
            break;
        case sf::Keyboard::Num9:
            addDigit(9);
            break;

    }
}

bool InputBox::pop()
{   
    if(!focus) return false;
    if(inp == 0) return false;
    inp /= 10;
    num.setString(std::to_string(inp));
    return true;
}

sf::RectangleShape InputBox::getBackground()
{
    return background;
}

sf::Text InputBox::getTitle()
{
    return title;
}

sf::Text InputBox::getNum()
{
    return num;
}

int InputBox::getValue()
{
    return inp;
}