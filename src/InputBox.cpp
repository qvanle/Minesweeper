#include <InputBox.hpp>

InputBox::InputBox() // construction
{
    background.setSize(sf::Vector2f(180, 60)); // set the size of background
    background.setFillColor(sf::Color(0, 128, 255)); // set color of background 
                                                     // (0, 128, 255): brescian blue
    inp = 0; // default value of box
    focus = false; // the box is not selected at the begin
    
    title.setFont(GraphicsData::font); // set font of title
    title.setCharacterSize(24); // set title character size (24px)
    title.setFillColor(sf::Color::White); // title color

    num.setFont(GraphicsData::font); // set font of num
    num.setCharacterSize(48); // set num character size (48px)
    num.setFillColor(sf::Color::White); // set color of num
    num.setString("0"); // default value (the same with inp)
}

void InputBox::setPosition(float x, float y)
{
    title.setPosition(x, y); // align title 
    background.setPosition(x + 480 , y - 15); // align background (shilf background to the right 480 px and shilf up a bit)
    num.setPosition(x + 510, y - 20); // align num (shilf num to the right 510px and shilf up a bit)
}

void InputBox::setTitle(std::string s) // pass a string s and set s as the title of the box
{   
    title.setString(s);
}

bool InputBox::isMouseInside(int x, int y) // pass mouse position (x, y), return true if (x, y) inside input area
{
    if(x < background.getPosition().x || background.getPosition().x + background.getSize().x <= x) 
        return false;
    if(y < background.getPosition().y || background.getPosition().y + background.getSize().y <= y)
        return false;
    return true;
}

void InputBox::setFocus(bool isFocus) // change focus of the box
{
    focus = isFocus;
    if(focus) 
    {
        background.setFillColor(sf::Color(128, 128, 255));
    }
    else 
    {
        background.setFillColor(sf::Color(0, 128, 255));
    }
}

bool InputBox::addDigit(int d) // pass an integer, if this box is focused, add d to the end of inp
{
    if(!focus) return false;
    if(d < 0 || d > 9) return false;
    inp = inp * 10 + d;
    num.setString(std::to_string(inp));
    return true;
}

void InputBox::setRange(int Lower, int Upper) // if inp is out of range [Lower, Upper], set it to closest value
{
    inp = std::max(inp, Lower);
    inp = std::min(inp, Upper);
    num.setString(std::to_string(inp));
}

void InputBox::typing(sf::Keyboard::Key code) // classify user input from keyboard
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

bool InputBox::pop() // erase the last digit of inp
{   
    if(!focus) return false;
    if(inp == 0) return false;
    inp /= 10;
    num.setString(std::to_string(inp));
    return true;
}

sf::RectangleShape InputBox::getBackground() // get background
{
    return background;
}

sf::Text InputBox::getTitle() // get title
{
    return title;
}

sf::Text InputBox::getNum() // get num
{
    return num;
}

int InputBox::getValue() // get inp
{
    return inp;
}